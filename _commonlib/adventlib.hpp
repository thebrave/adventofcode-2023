#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <cassert>

class adventlib
{
public:
    static std::vector<std::string> readLines(const std::string &filename);
    static std::string trim(const std::string &str);
    static bool endsWith(const std::string &str, const std::string &suffix);
    static std::string replaceAll(std::string str, const std::string &from, const std::string &to);
    static std::vector<std::string> splitString(const std::string &s, const std::string &delim);
};
