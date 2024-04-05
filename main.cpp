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

    std::cout << largeMaxFlow << '\n';

    removePipe(&largeDataset, "R_13", "PS_42");

    std::cout << maxFlow(largeDataset) << '\n';

    auto deficits = createDeficitsCities(largeDataset);
    auto pipesDeficits = createDeficitsPipes(largeDataset);

    //showStatisticsDeficit(deficits,largeMaxFlow);
    //showStatisticsDeficit(pipesDeficits,largeMaxFlow);

    return 0;
}

double maxFlow(Dataset dataset) {

    Graph newGraph = dataset.getNetwork();
    int maxFlow = edmondsKarp(&(newGraph),"SUPER_SOURCE","SUPER_SINK");
    return maxFlow;
}

