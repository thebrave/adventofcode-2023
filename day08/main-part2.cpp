#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <string>
#include <tuple>
#include <vector>

#include <cassert>
#include <cmath>

#include "adventlib.hpp"

using namespace std;

std::tuple<std::string, std::string, std::string>
extractSubstrings(const std::string &str)
{

    std::regex pattern{"(\\w{3}) = \\((\\w{3}), (\\w{3})\\)"};

    std::smatch matches;
    if (std::regex_search(str, matches, pattern))
    {
        return {matches[1], matches[2], matches[3]};
    }

    return {"", "", ""};
}

void calculateFileValue(const std::string &filename)
{
    const auto lines = adventlib::readLines(filename);

    // Sanity checks
    assert(lines.size() > 2);
    assert(lines[0].size() > 0);
    assert(lines[1].size() == 0);

    const string &directions = lines[0];
    std::cout << filename << " directions: " << directions << std::endl;

    map<string, pair<string, string>> worldMap;

    for (int i = 2; i < lines.size(); i++)
    {
        const auto [name, a, b] = extractSubstrings(lines[i]);

        // Check that we got everything we needed
        assert(name.size() > 0);
        assert(a.size() > 0);
        assert(b.size() > 0);

        worldMap[name] = {a, b};
    }

    list<string> current_positions;
    for_each(worldMap.cbegin(), worldMap.cend(),
             [&current_positions](const auto &entry)
             {
                 if (adventlib::endsWith(entry.first, "A"))
                 {
                     current_positions.push_back(entry.first);
                 }
             });

    auto iter = directions.cbegin();
    uint value = 0;

    while (std::any_of(current_positions.cbegin(), current_positions.cend(), [](const string &p)
                       { return !adventlib::endsWith(p, "Z"); }))
    {
        // cout << filename << " - total: " << std::to_string(value) << "Current positions: "
        //      << to_string(std::count_if(current_positions.cbegin(), current_positions.cend(), [](const string &p)
        //                                 { return !adventlib::endsWith(p, "Z"); }))
        //      << endl;

        // for_each(current_positions.begin(), current_positions.end(),
        //          [](const auto &entry)
        //          {
        //              cout << " - Pos: " << entry << endl;
        //          });

        bool broken(false);
        for (string &pos : current_positions)
        {
            if (*iter == 'L')
            {
                pos = worldMap[pos].first;
            }
            else if (*iter == 'R')
            {
                pos = worldMap[pos].second;
            }
            else
            {
                broken = true;
                assert(false);
            }
        }

        ++value;
        ++iter;
        if (iter == directions.cend() || broken)
        {
            iter = directions.cbegin();
        }
    }

    std::cout << filename << " - finished ?" << std::endl;

    for_each(current_positions.begin(), current_positions.end(),
             [](const auto &entry)
             {
                 cout << " - Pos: " << entry << endl;
             });

    std::cout << filename << " - total: " << std::to_string(value) << std::endl;
}

int main()
{
    const string directory = "/workspaces/adventofcode-2023/day08/input";

    for (const auto &entry : filesystem::directory_iterator(directory))
    {
        if (adventlib::endsWith(entry.path().string(), ".txt"))
        {
            calculateFileValue(entry.path().string());
        }
        else
        {
            cout << "Skipping " << entry.path() << endl;
        }
    }

    return 0;
}