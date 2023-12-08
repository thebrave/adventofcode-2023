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
extractSubstrings(const std::string &str) {

  std::regex pattern {"(\\w{3}) = \\((\\w{3}), (\\w{3})\\)"};
  
  std::smatch matches;
  if (std::regex_search(str, matches, pattern)) {
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

    const string& directions=lines[0];

    map<string, pair< string, string>> worldMap;

    for(int i=2; i<lines.size(); i++)
    {
        const auto [name, a, b] = extractSubstrings(lines[i]);

        // Check that we got everything we needed
        assert(name.size() > 0);
        assert(a.size() > 0);
        assert(b.size() > 0);

        worldMap[name] = {a, b};
    }

    while()

    //std::cout << filename << " - " << count << " items - total: " << std::to_string(value) << std::endl;
}

int main()
{
    const string directory = "C:/Users/jeanb/Workspace/adventofcode-2023/day08/input";

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