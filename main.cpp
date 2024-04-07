#include "classes/Dataset.cpp"
#include "classes/Edmonds_Karps.cpp"
#include "classes/Menu.cpp"
#include "classes/Utils.cpp"
#include "classes/Graph.cpp"
#include "classes/Parser.cpp"
#include <iostream>



double maxFlow(Dataset dataset);

int main() {



    Menu menu;
    Dataset dataset;
    Dataset* datasetPtr = nullptr; // Declare a pointer to Dataset and initialize it to nullptr

    int datasetPicker = menu.DatasetMenu();
    if (datasetPicker == 1){
        dataset = createSmallDataset();
        datasetPtr = &dataset; // Assign the address of dataset to datasetPtr
        datasetPtr->prepareSuperNodes(); // Access members using -> when using pointers
    }
    else if (datasetPicker == 2){
        dataset = createLargeDataset();
        dataset.prepareSuperNodes(); // Call prepareSuperNodes directly on dataset
        datasetPtr = &dataset; // Assign the address of dataset to datasetPtr
    }

    menu.MainMenu(dataset); // Pass dataset, not datasetPtr


}



double maxFlow(Dataset dataset) {

    Graph newGraph = dataset.getNetwork();
    int maxFlow = edmondsKarp(&(newGraph),"SUPER_SOURCE","SUPER_SINK");
    return maxFlow;
}

