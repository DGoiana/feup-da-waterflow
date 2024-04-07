#include "classes/Menu.cpp"



double maxFlow(Dataset dataset);
int DatasetMenu();

int main() {

    Dataset dataset;

    int datasetPicker = DatasetMenu();
    if (datasetPicker == 1){
        dataset = createSmallDataset();
    }
    else if (datasetPicker == 2){
        dataset = createLargeDataset();
         // Assign the address of dataset to datasetPtr
    }

    Menu menu(dataset);

    menu.MainMenu(); // Pass dataset, not datasetPtr


}

int DatasetMenu() {
    std::cout << "\n\n ----------------------------------------------\n"
                 "|                 Dataset Menu                  |\n"
                 " ----------------------------------------------\n";
    std::cout << "Hello, water supply manager!\n";
    std::cout << "Select the number of the topic...\n"
                 "[1]> Small Dataset\n"
                 "[2]> Large Dataset\n"

                 "\n[0]> Quit\n";

    int topic_in_graph_menu;
    std::string striTemp;

    while (true) {
        topic_in_graph_menu = 0;
        striTemp = "";
        std::cin >> striTemp;
        try {
            topic_in_graph_menu = stoi(striTemp);
        }
        catch (...) {
            topic_in_graph_menu = 100;
        }

        if (topic_in_graph_menu == 1) {
            return 1;
            break;
        } else if (topic_in_graph_menu == 2) {
            return 2;
            break;
        }

        else if (topic_in_graph_menu == 0) break;
        else std::cout << "Error: Choose one number of the Main Menu.\n";
    }
    return 0;
}


double maxFlow(Dataset dataset) {

    Graph newGraph = dataset.getNetwork();
    int maxFlow = edmondsKarp(&(newGraph),"SUPER_SOURCE","SUPER_SINK");
    return maxFlow;
}

