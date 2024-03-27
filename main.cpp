#include "classes/Graph.h"
#include "classes/Parser.h"
#include "classes/Dataset.h"
#include <iostream>

void testGraphBasicFunctions();
int main() {
    Parser parser;

    std::list<std::vector<std::string> > cities = parser.readFile("small_dataset/Cities_Madeira.csv");
    std::list<std::vector<std::string> > reservoirs = parser.readFile("small_dataset/Reservoirs_Madeira.csv");
    std::list<std::vector<std::string> > stations = parser.readFile("small_dataset/Stations_Madeira.csv");
    std::list<std::vector<std::string> > pipes = parser.readFile("small_dataset/Pipes_Madeira.csv");

    Dataset dataset = Dataset(cities, pipes, stations, reservoirs);

    for(Node* n : dataset.getNetwork().getNodeSet()){
        std::cout << n->getInfo().getCode();
    }
}