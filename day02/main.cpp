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

std::vector<std::string> splitString(const std::string &s, const std::string &delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delim[0]))
    {
        tokens.push_back(token);
    }
    return tokens;
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

void calculateFileValue(const std::string &filename)
{
    const std::map<int, std::string> digits =
        {
            {"blue", 14},
            {"red", 12},
            {"green", 13}};

    auto lines = readLines(filename);
    int value = 0;
    int count = 0;

    for (auto const &line : lines)
    {
        size_t id_sep = line.find(':');

        assert(id_sep != std::string::npos);

        auto games = splitString(line.substr(id_sep + 1), ";");

        assert(games.size() != 0);

        for (const auto &game : games)
        {
        }

        std::cout << "l: " << original << " m: " << line << " v: " << str_val << std::endl;
    }

    std::cout << filename << " - " << count << " items - total: " << std::to_string(value) << std::endl;
}

int main()
{
    const std::string directory = "input";

    for (const auto &entry : std::filesystem::directory_iterator(directory))
    {
        calculateFileValue(entry.path(), digits);
    }

    return 0;
}
