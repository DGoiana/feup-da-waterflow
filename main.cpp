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
    auto deficits = createDeficitsCities(smallDataset);
    auto pipesDeficits = createDeficitsPipes(smallDataset);

    showStatisticsDeficit(deficits,smallMaxFlow);
    showStatisticsDeficit(pipesDeficits,smallMaxFlow);

    return 0;
}

double maxFlow(Dataset dataset) {

    Graph newGraph = dataset.getNetwork();
    int maxFlow = edmondsKarp(&(newGraph),"SUPER_SOURCE","SUPER_SINK");
    return maxFlow;
}

