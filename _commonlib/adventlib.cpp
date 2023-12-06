#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <cassert>

#include "adventlib.hpp"

std::vector<std::string> adventlib::readLines(const std::string &filename)
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