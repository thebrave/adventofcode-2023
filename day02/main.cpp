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

std::string trim(const std::string &str)
{
    return str.substr(str.find_first_not_of(" "), str.find_last_not_of(" ") - str.find_first_not_of(" ") + 1);
}

bool endsWith(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() && str.substr(str.size() - suffix.size()) == suffix;
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
    const std::map<std::string, int> digits =
        {
            {"blue", 14},
            {"red", 12},
            {"green", 13}};

    auto lines = readLines(filename);
    int value = 0;
    int count = 0;

    for (auto const &line : lines)
    {
        // For every game
        size_t id_sep = line.find(':');

        assert(id_sep != std::string::npos);
        assert(line.substr(0, 5) == "Game ");

        // std::cout << filename << " - " << line.substr(5, id_sep - 5) << std::endl;
        const int id = std::stoi(line.substr(5, id_sep - 5));

        auto games = splitString(line.substr(id_sep + 1), ";");

        assert(games.size() != 0);

        bool is_valid(true);

        for (const auto &game : games)
        {
            // For every set
            auto cubes(digits);

            // Reset counters
            for (auto &cube : cubes)
            {
                cubes[cube.first] = 0;
            }

            auto parts = splitString(game, ",");
            assert(parts.size() <= digits.size());

            for (const auto &part : parts)
            {
                // For every cube in a set
                // std::cout << filename << " - " << trim(part) << std::endl;
                auto parts = splitString(trim(part), " ");
                assert(parts.size() == 2);

                int part_value = std::stoi(trim(parts[0]));
                assert(part_value != std::string::npos);

                const std::string &part_color = parts[1];

                assert(cubes.find(part_color) != cubes.end());

                cubes[part_color] += part_value;
            }

            for (const auto &ref : digits)
            {
                assert(cubes.find(ref.first) != cubes.end());

                if (ref.second < cubes[ref.first])
                {
                    is_valid = false;
                    break;
                }
            }

            if (!is_valid)
            {
                break;
            }
        }

        if (is_valid)
        {
            value += id;
        }
    }

    std::cout << filename << " - " << count << " items - total: " << std::to_string(value) << std::endl;
}

int main()
{
    const std::string directory = "/workspaces/adventofcode-2023/day02/input";

    for (const auto &entry : std::filesystem::directory_iterator(directory))
    {
        if (endsWith(entry.path(), ".txt"))
        {
            calculateFileValue(entry.path());
        }
        else
        {
            std::cout << "Skipping " << entry.path() << std::endl;
        }
    }

    return 0;
}
