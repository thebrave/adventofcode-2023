#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <cassert>

using namespace std;

std::vector<std::string> readLines(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    return lines;
}

std::string replaceAll(std::string str, const std::string &from, const std::string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

void replaceAll(std::string &str, const std::map<int, std::string> &map)
{
    size_t start_pos = 0;
    bool did_something(false);
    do
    {
        did_something = false;
        for (int i = 0; i < str.length(); i++)
        {
            for (const auto &digit : map)
            {
                if (str.substr(i, digit.second.length()) == digit.second)
                {
                    str.replace(i, digit.second.length(), std::to_string(digit.first));
                    did_something = true;
                    break;
                }
            }

            if (did_something)
            {
                continue;
            }
        }
    } while (did_something);
}

void calculateFileValue(const std::string &filename, const std::map<int, std::string> &digits)
{
    auto lines = readLines(filename);
    int value = 0;
    int count = 0;

    for (auto line : lines)
    {
        auto original(line);

        replaceAll(line, digits);
        // std::cout << "l: " << original << " m: " << line << std::endl;

        size_t pos1 = line.find_first_of("0123456789");
        size_t pos2 = line.find_last_of("0123456789");

        assert(pos1 != string::npos);
        assert(pos2 != string::npos);

        auto str_val = line.substr(pos1, 1) + line.substr(pos2, 1);
        value += std::stoi(str_val);
        count++;

        std::cout << "l: " << original << " m: " << line << " v: " << str_val << std::endl;
    }

    std::cout << filename << " - " << count << " items - total: " << std::to_string(value) << std::endl;
}

int main()
{
    std::map<int, std::string> digits =
        {
            {1, "one"},
            {2, "two"},
            {3, "three"},
            {4, "four"},
            {5, "five"},
            {6, "six"},
            {7, "seven"},
            {8, "eight"},
            {9, "nine"},
        };

    const std::string directory = "/workspaces/adventofcode-2023/day01/input";

    for (const auto &entry : std::filesystem::directory_iterator(directory))
    {
        calculateFileValue(entry.path(), digits);
    }

    return 0;
}
