#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <cassert>

#include "adventlib.hpp"

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
        assert(line.substr(0, 5) == "Game ");

        // std::cout << filename << " - " << line.substr(5, id_sep - 5) << std::endl;
        const int id = std::stoi(line.substr(5, id_sep - 5));

        auto games = adventlib::splitString(line.substr(id_sep + 1), ";");

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

            auto parts = adventlib::splitString(game, ",");
            assert(parts.size() <= digits.size());

            for (const auto &part : parts)
            {
                // For every cube in a set
                // std::cout << filename << " - " << trim(part) << std::endl;
                auto parts = adventlib::splitString(adventlib::trim(part), " ");
                assert(parts.size() == 2);

                int part_value = std::stoi(adventlib::trim(parts[0]));
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
    const std::string directory = "input";

    for (const auto &entry : std::filesystem::directory_iterator(directory))
    {
        if (adventlib::endsWith(entry.path(), ".txt"))
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
