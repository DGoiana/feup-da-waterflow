#include "classes/Parser.h"
#include "classes/Dataset.h"
#include "classes/Edmonds_Karps.h"
#include "classes/Utils.cpp"

#include "City.h"

Dataset createSmallDataset();
Dataset createLargeDataset();
double maxFlow(Dataset dataset);

int main() {
    Dataset largeDataset = createLargeDataset();
    largeDataset.prepareSuperNodes();

     Dataset smallDataset = createSmallDataset();
    smallDataset.prepareSuperNodes();
    double largeMaxFlow = maxFlow(largeDataset);
    double smallMaxFlow = maxFlow(smallDataset);
    auto deficits = createDeficits(largeDataset);

    showStatisticsDeficit(deficits,smallMaxFlow);
    return 0;
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
    std::list<std::vector<std::string> > pipes = parser.readFile("../large_dataset/Pipes.csv");

    return Dataset(cities, pipes, stations, reservoirs);
}

double maxFlow(Dataset dataset) {
    Node *superSource = dataset.getNetwork().findNode("SUPER_SOURCE");
    Node *superSink = dataset.getNetwork().findNode("SUPER_SINK");

    Graph newGraph = dataset.getNetwork();

    int maxFlow = edmondsKarp(&(newGraph),"SUPER_SOURCE","SUPER_SINK");

    return maxFlow;
    /*
    // FOR SHOWING PURPOSES


    std::cout << "SUPER_SOURCE\n";
    for(Pipe *p: superSource->getPipes()) {
        std::cout << p->getDest()->getInfo()->getCode() <<"(" << p->getDest()->getInfo()->getCode() <<")" <<  ":" << p->getFlow() << "(FLOW)\n";
    }
    std::cout << '\n';
    std::cout << "SUPER_SINK\n";
    for(Pipe *p: superSink->getIncoming()) {
        std::cout << p->getOrig()->getInfo()->getCode() << ":" << p->getFlow() << "(FLOW)\n";
        maxFluxo += p->getFlow();
    }
    std::cout << "MAX_FLOW: " << maxFlow <<'\n';
    std::cout << "MAX_FLOW: " << maxFluxo <<'\n';
     */
}

