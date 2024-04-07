#include "Parser.h"
#include <iostream>
#include <fstream>
#include <filesystem>

std::vector<std::string> Parser::split(std::string line, const std::string &delimiter){
   size_t pos;
   std::string token;
   std::vector<std::string> result;
   while(line.find(delimiter) != std::string::npos) {
      pos = line.find(delimiter);
      token = line.substr(0,pos);
      result.push_back(token);
      line = line.substr(pos + delimiter.length());
   }
   result.push_back(line.substr(0));
   return result;
}


std::list<std::vector<std::string> > Parser::readFile(const std::string &path) {
    std::cout << std::filesystem::current_path() << '\n';
   std::ifstream file(path);
   std::string line;
   std::list<std::vector<std::string>> result;
   while (getline(file,line)) {
       line = line.substr(0,line.length() + 1 - 2 );
       result.push_back(split(line,","));
   }
   file.close();
   result.pop_front();
   return result;
}

std::list<std::vector<std::string>> Parser::parseCities(const std::string &path) {
    auto rawCities = readFile(path);
    for(auto &v : rawCities) {
        v[4].append(v[5]);
        v[4] = v[4].substr(1,v[4].length()-2);
    }
    return rawCities;
}
