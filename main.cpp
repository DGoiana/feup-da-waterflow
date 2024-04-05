#include "classes/Dataset.h"
#include "classes/Edmonds_Karps.h"
#include "classes/Utils.cpp"

double maxFlow(Dataset dataset);

int main() {
    Dataset largeDataset = createLargeDataset();
    largeDataset.prepareSuperNodes();


    Dataset smallDataset = createSmallDataset();
    smallDataset.prepareSuperNodes();

    double largeMaxFlow = maxFlow(largeDataset);
    double smallMaxFlow = maxFlow(smallDataset);

    balanceNetwork(&largeDataset);

    return 0;
}

double maxFlow(Dataset dataset) {

    Graph newGraph = dataset.getNetwork();
    int maxFlow = edmondsKarp(&(newGraph),"SUPER_SOURCE","SUPER_SINK");
    return maxFlow;
}

