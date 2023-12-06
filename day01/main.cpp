#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <map>

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

std::string replaceAll(std::string str, const std::map<int, std::string> &map)
{
    size_t start_pos = 0;
    for (auto substr : map)
    {
    }
    return str;
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

    auto lines = readLines("input/sample.txt");
    int value = 0;

    for (auto line : lines)
    {
        auto original(line);

        for (auto &digit : digits)
        {
            line = replaceAll(line, digit.second, std::to_string(digit.first));
        }

        size_t pos1 = line.find_first_of("0123456789");
        size_t pos2 = line.find_last_of("0123456789");

        assert(pos1 != string::npos);
        assert(pos2 != string::npos);

        auto str_val = line.substr(pos1, 1) + line.substr(pos2, 1);
        value += std::stoi(str_val);

        std::cout << "l: " << original << " m: " << line << " v: " << str_val << std::endl;
    }

    std::cout << "Total: " << std::to_string(value) << std::endl;

    return 0;
}
