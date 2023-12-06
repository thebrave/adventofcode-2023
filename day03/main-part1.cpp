#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <functional>

#include <cassert>

#include "adventlib.hpp"

using namespace std;

bool isSymbol(const vector<string> &lines, int x, int y)
{
    // cout << "isSymbol: " << x << "," << y << endl;

    if (x < 0 || y < 0 || y >= lines.size() || x >= lines.at(y).size())
    {
        return false;
    }

    const auto c = lines.at(y).at(x);

    if (c != '.')
    {
        // cout << ">>>> " << lines.at(y).substr(x, 1) << endl;
    }

    return c != '.';
}

bool any_true(const vector<string> &lines,
              const list<pair<int, int>> &numbers,
              function<bool(const vector<string> &lines, int, int)> lambda)
{
    for (const auto &coordinate : numbers)
    {
        if (lambda(lines, coordinate.first, coordinate.second))
        {
            return true;
        }
    }
    return false;
}

int check_num(const vector<string> &lines, int x, int y, size_t len)
{
    // cout << "check_num: " << x << "," << y << ", len:" << to_string(len) << endl;
    list<pair<int, int>> l;

    for (int i = 0; i <= len + 2; i++)
    {
        l.push_back(make_pair(i + x - 1, y - 1));
        l.push_back(make_pair(i + x - 1, y + 1));
    }

    l.push_back(make_pair(x - 1, y));
    l.push_back(make_pair(x + len, y));

    return any_true(lines, l, isSymbol);
}

void calculateFileValue(const string &filename)
{
    auto lines = adventlib::readLines(filename);
    int value = 0;
    int size_w = lines.size();
    int size_h = lines.at(0).size();

    for (int y = 0; y < size_h; y++)
    {
        // cout << ">> line: " << to_string(y) << endl;
        for (int x = 0; x < size_w; x++)
        {
            // cout << ">>> row: " << lines.at(y).substr(x) << endl;
            if (isdigit(lines.at(y).at(x)))
            {
                // cout << ">>> " << lines.at(y).substr(x, 1) << " is a digit" << endl;

                int len = lines.at(y).substr(x).find_first_not_of("0123456789");
                if (len == string::npos)
                {
                    cout << ">>> up to end of line" << endl;
                    len = lines.at(y).size() - 1;
                }

                const string number = lines.at(y).substr(x, len);

                if (check_num(lines, x, y, len))
                {
                    // cout << ">>> " << number << " is a part number, len:" << to_string(len) << endl;
                    value += stoi(number);
                }
                else
                {
                    // cout << ">>> " << number << " is ignored, len:" << to_string(len) << endl;
                }

                if (x + len >= lines.at(y).size() - 1)
                {
                    break;
                }
                else
                {
                    x += len;
                }
            }
        }
    }

    cout << filename << " - " << size_w << "x" << size_h << " - value: " << to_string(value) << endl;
}

int main()
{
    const string directory = "/workspaces/adventofcode-2023/day03/input";

    for (const auto &entry : filesystem::directory_iterator(directory))
    {
        if (adventlib::endsWith(entry.path(), ".txt"))
        {
            calculateFileValue(entry.path());
        }
        else
        {
            cout << "Skipping " << entry.path() << endl;
        }
    }

    return 0;
}