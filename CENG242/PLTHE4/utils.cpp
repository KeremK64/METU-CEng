#include "utils.hpp"

std::vector<std::string> parse_line(const std::string& line, const char delimiter)
{
    std::vector<std::string> res;
    std::string parsed;
    std::istringstream ss(line);
    while(std::getline(ss, parsed, delimiter))
        res.push_back(parsed);
    return res;
}