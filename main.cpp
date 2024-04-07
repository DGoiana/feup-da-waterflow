#include "classes/Menu.cpp"



double maxFlow(Dataset dataset);

int main() {



    Menu menu;
    Dataset dataset;
    Dataset* datasetPtr = nullptr; // Declare a pointer to Dataset and initialize it to nullptr

    int datasetPicker = menu.DatasetMenu();
    if (datasetPicker == 1){
        dataset = createSmallDataset();
    }
    else if (datasetPicker == 2){
        dataset = createLargeDataset();
         // Assign the address of dataset to datasetPtr
    }

    menu.MainMenu(dataset); // Pass dataset, not datasetPtr


}



double maxFlow(Dataset dataset) {

    Graph newGraph = dataset.getNetwork();
    int maxFlow = edmondsKarp(&(newGraph),"SUPER_SOURCE","SUPER_SINK");
    return maxFlow;
}

