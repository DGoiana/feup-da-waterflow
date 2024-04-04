#include "classes/Dataset.h"
#include "classes/Edmonds_Karps.h"
#include "classes/Utils.cpp"

double maxFlow(Dataset dataset);

int main() {
    Dataset largeDataset = createLargeDataset();
    largeDataset.prepareSuperNodes();


     Dataset smallDataset = createSmallDataset();
    smallDataset.prepareSuperNodes();

    double  largeMaxFlow = maxFlow(largeDataset);
    //auto deficits = createDeficits(smallDataset);

    //showStatisticsDeficit(deficits,largeMaxFlow);

    removeNode(&largeDataset, "R_13");

    return 0;
}

double maxFlow(Dataset dataset) {
    Node *superSource = dataset.getNetwork().findNode("SUPER_SOURCE");
    Node *superSink = dataset.getNetwork().findNode("SUPER_SINK");

    Graph newGraph = dataset.getNetwork();

    int maxFlow = edmondsKarp(&(newGraph),"SUPER_SOURCE","SUPER_SINK");
    return maxFlow;

    //FOR SHOWING PURPOSES


    /* std::cout << "SUPER_SOURCE\n";
    for(Pipe *p: superSource->getPipes()) {
        std::cout << p->getDest()->getInfo()->getCode() <<"(" << p->getDest()->getInfo()->getCode() <<")" <<  ":" << p->getFlow() << "(FLOW)\n";
    }
    std::cout << '\n';
    std::cout << "SUPER_SINK\n";
    for(Pipe *p: superSink->getIncoming()) {
        std::cout << p->getOrig()->getInfo()->getCode() << ":" << p->getFlow() << "(FLOW)\n";
    }
    std::cout << "MAX_FLOW: " << maxFlow <<'\n'; */

}

