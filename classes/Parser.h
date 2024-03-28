#ifndef DA_FLOW_NETWORK_PARSER_H
#define DA_FLOW_NETWORK_PARSER_H

#include <vector>
#include <string>
#include <list>

class Parser{
   public:
    std::vector<std::string> split(std::string line, const std::string& delimiter);
    std::list<std::vector<std::string>> parseCities(const std::string &path);
    std::list<std::vector<std::string> > readFile(const std::string &path);
};

#endif