#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <cassert>

#include "adventlib.hpp"

std::string adventlib::trim(const std::string &str)
{
    if(str.find_first_not_of(" ") == std::string::npos)
    {
        return "";
    }

    return str.substr(str.find_first_not_of(" "), str.find_last_not_of(" ") - str.find_first_not_of(" ") + 1);
}

bool adventlib::endsWith(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() && str.substr(str.size() - suffix.size()) == suffix;
}

std::string adventlib::replaceAll(std::string str, const std::string &from, const std::string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

std::vector<std::string> adventlib::splitString(const std::string &s, const std::string &delim)
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