#include "vector"
#include "string"
#include "City.h"
#include "Reservoir.h"
#include "Dataset.h"
#include "Edmonds_Karps.h"
#include "Parser.h"
#include <iostream>
#include <algorithm>
#include <complex>

Dataset createSmallDataset() {
    Parser parser;

    std::list<std::vector<std::string> > cities = parser.parseCities("../small_dataset/Cities_Madeira.csv");
    std::list<std::vector<std::string> > reservoirs = parser.readFile("../small_dataset/Reservoirs_Madeira.csv");
    std::list<std::vector<std::string> > stations = parser.readFile("../small_dataset/Stations_Madeira.csv");
    stations.pop_back();
    std::list<std::vector<std::string> > pipes = parser.readFile("../small_dataset/Pipes_Madeira.csv");

    return Dataset(cities, pipes, stations, reservoirs);
}

Dataset createLargeDataset() {
    Parser parser;

    std::list<std::vector<std::string> > cities = parser.parseCities("../large_dataset/Cities.csv");
    std::list<std::vector<std::string> > reservoirs = parser.readFile("../large_dataset/Reservoir.csv");
    std::list<std::vector<std::string> > stations = parser.readFile("../large_dataset/Stations.csv");
    std::list<std::vector<std::string> > pipes = parser.readFile("../large_dataset/Pipes.csv");

    return Dataset(cities, pipes, stations, reservoirs);
}

double calculate_variance(const std::vector<std::pair<std::string, int>>& data) {
    if (data.empty()) {
        return 0.0; // Return 0 if the input vector is empty
    }

    // Calculate mean
    double mean = 0.0;
    for (const auto& pair : data) {
        mean += pair.second;
    }
    mean /= data.size();

    // Calculate squared differences from the mean
    double squared_diff = 0.0;
    for (const auto& pair : data) {
        squared_diff += std::pow(pair.second - mean, 2);
    }

    // Calculate variance
    double variance = squared_diff / data.size();
    return variance;
}

void showStatisticsDeficit(std::vector<std::pair<std::string,int>> deficits, double maxFlow) {
    std::cout << "Deficit Stats" << '\n';

    for(auto d : deficits) {
        if(d.second != 0) std::cout << d.first << " " << d.second << '\n';
    }

    std::cout << "Variance: " << std::sqrt(calculate_variance(deficits)) << '\n';
    // Calculate mean
    double mean = 0.0;
    for (const auto &pair: deficits) {
        mean += pair.second;
    }
    mean /= deficits.size();

    std::cout << "Mean: " << mean << '\n';
    auto maxDiff = *(std::max_element(deficits.begin(), deficits.end(),
                                      [](auto a, auto b) { return a.second < b.second; }));
    std::cout << "Max difference: " << maxDiff.second << '\n';
    std::cout << "Max flow: " << maxFlow << '\n';
}

std::vector<std::pair<std::string,int>> createDeficits(Dataset *dataset) {
    std::vector<std::pair<std::string,int>> deficitCities;

    for(Node *node: dataset->getNetwork().getNodeSet()) {
        if(node->getInfo()->getCode().substr(0,1) == "C") {
            double sumFlow = 0;
            double cityDemand = dynamic_cast<City*>(node->getInfo())->getDeliveryDemand();

            for(Pipe *p: node->getIncoming()) {
                sumFlow += p->getFlow();
            }
            if(node->getInfo()->getCode().substr(0,1) == "C")
                deficitCities.push_back({node->getInfo()->getCode(),cityDemand - sumFlow});
        }
    }
    return deficitCities;
}

void removeNode(Dataset *dataset, std::string code){
    Node* nodeToRemove = dataset->getNetwork().findNode(code); // find node to remove

    std::vector<Pipe*> oldOutgoingPipes = nodeToRemove->getPipes();
    std::vector<Pipe*> oldIncomingPipes = nodeToRemove->getIncoming();

    Graph _graph = dataset->getNetwork(); // get graph

    int initialFlow = edmondsKarp(&_graph, "SUPER_SOURCE", "SUPER_SINK"); // run initial flow
    std::vector<std::pair<std::string, int>> initialDeficits = createDeficits(dataset); // create initial deficits

    _graph.removeNode(*nodeToRemove->getInfo()); // remove node

    int middleFlow = edmondsKarp(&_graph, "SUPER_SOURCE", "SUPER_SINK"); // run updated flow
    std::vector<std::pair<std::string, int>> finalDeficits = createDeficits(dataset); // create updated deficits

    showStatisticsDeficit(initialDeficits, initialFlow);
    showStatisticsDeficit(finalDeficits, middleFlow);

    /*
    for(int i = 0; i < initialDeficits.size(); i++){
        if(initialDeficits[i].second != finalDeficits[i].second){
            std::cout << "The city " << dynamic_cast<City*>(_graph.findNode(initialDeficits[i].first)->getInfo())->getName() << " (" << _graph.findNode(initialDeficits[i].first)->getInfo()->getCode() <<  ") has changed it's deficit from " << initialDeficits[i].second << " to " << finalDeficits[i].second << '\n';
        }
    } */

    for(auto p: oldOutgoingPipes){
        nodeToRemove->addPipe(p->getDest(), p->getCapacity());
    }

    for(auto p: oldIncomingPipes){
        p->getOrig()->addPipe(nodeToRemove, p->getCapacity());
    }
}