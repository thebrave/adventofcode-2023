#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <functional>

#include <cassert>

#include "adventlib.hpp"
#include <cmath>

using namespace std;

void calculateFileValue(const std::string &filename)
{
    const std::map<std::string, int> digits =
        {
            {"blue", 14},
            {"red", 12},
            {"green", 13}};

    auto lines = adventlib::readLines(filename);
    int value = 0;
    int count = 0;

    for (auto const &line : lines)
    {
        // For every game
        size_t id_sep = line.find(':');

        assert(id_sep != std::string::npos);
        assert(line.substr(0, 5) == "Card ");

        // std::cout << filename << " - " << line.substr(5, id_sep - 5) << std::endl;
        const int id = std::stoi(line.substr(5, id_sep - 5));

        auto games = adventlib::splitString(line.substr(id_sep + 1), "|");

        assert(games.size() == 2);

        set<int> winning;
        auto parts = adventlib::splitString(adventlib::trim(games.at(0)), " ");
        assert(parts.size() > 0);

        for (const auto &part : parts)
        {
            const std::string part_str = adventlib::trim(part);
            if (part_str.empty())
            {
                continue;
            }
            int part_value = std::stoi(part_str);
            winning.insert(part_value);
        }

        int winning_count = 0;
        std::cout << filename << " -" << adventlib::trim(games.at(1)) << "-" << std::endl;
        parts = adventlib::splitString(adventlib::trim(games.at(1)), " ");
        assert(parts.size() > 0);

        for (const auto &part : parts)
        {
            const std::string part_str = adventlib::trim(part);
            if (part_str.empty())
            {
                continue;
            }
            int part_value = std::stoi(part_str);
            if (winning.count(part_value) > 0)
            {
                ++winning_count;
            }
        }

        int points = 0;
        if (winning_count > 0)
        {
            points += pow(2, winning_count - 1);
        }

        value += points;

        std::cout << filename << " - card: " << std::to_string(id) << " - "
                  << std::to_string(winning_count) << " winning => "
                  << std::to_string(points) << " points" << std::endl;
    }

    std::cout << filename << " - " << count << " items - total: " << std::to_string(value) << std::endl;
}

int main()
{
    const string directory = "/workspaces/adventofcode-2023/day04/input";

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