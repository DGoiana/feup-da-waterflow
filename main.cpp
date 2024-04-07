#include "classes/Dataset.h"
#include "classes/Edmonds_Karps.h"
#include "classes/Menu.cpp"
#include "classes/Utils.cpp"
#include <iostream>

Dataset createSmallDataset();
Dataset createLargeDataset();


double maxFlow(Dataset dataset);

int main() {
    Dataset dataset = createLargeDataset();
    dataset.prepareSuperNodes();


    Menu menu(dataset);
}

Dataset createSmallDataset() {
    Parser parser;

    removePipe(&largeDataset, "R_13", "PS_42");

    std::cout << maxFlow(largeDataset) << '\n';

    return 0;
}

double maxFlow(Dataset dataset) {

    Graph newGraph = dataset.getNetwork();
    int maxFlow = edmondsKarp(&(newGraph),"SUPER_SOURCE","SUPER_SINK");
    return maxFlow;
}

