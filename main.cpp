#include "classes/Parser.h"
#include "classes/Dataset.h"
#include "classes/Edmonds_Karps.h"
#include <iostream>

Dataset createSmallDataset();
Dataset createLargeDataset();
void maxFlow(Dataset dataset);

int main() {
    Dataset largeDataset = createLargeDataset();
    largeDataset.prepareSuperNodes();

    Dataset smallDataset = createSmallDataset();
    smallDataset.prepareSuperNodes();

    maxFlow(largeDataset);
    //std::cout << '\n';
    //maxFlow(smallDataset);
}

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
    stations.pop_back();
    std::list<std::vector<std::string> > pipes = parser.readFile("../large_dataset/Pipes.csv");

    return Dataset(cities, pipes, stations, reservoirs);
}

void maxFlow(Dataset dataset) {
    Node *superSource = dataset.getNetwork().findNode("SUPER_SOURCE");
    Node *superSink = dataset.getNetwork().findNode("SUPER_SINK");

    Graph newGraph = dataset.getNetwork();

    int maxFlow = edmondsKarp(&(newGraph),"SUPER_SOURCE","SUPER_SINK");
    int maxFluxo = 0;

    // FOR SHOWING PURPOSES
    std::cout << "SUPER_SOURCE\n";
    for(Pipe *p: superSource->getPipes()) {
        std::cout << p->getDest()->getInfo().getCode() <<"(" << p->getDest()->getInfo().getCode() <<")" <<  ":" << p->getFlow() << "(FLOW)\n";
    }
    std::cout << '\n';
    std::cout << "SUPER_SINK\n";
    for(Pipe *p: superSink->getIncoming()) {
        std::cout << p->getOrig()->getInfo().getCode() << ":" << p->getFlow() << "(FLOW)\n";
        maxFluxo += p->getFlow();
    }
    std::cout << "MAX_FLOW: " << maxFlow <<'\n';
    std::cout << "MAX_FLOW: " << maxFluxo <<'\n';
}
