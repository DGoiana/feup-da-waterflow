//
// Created by ritac on 25/03/2024.
//

#include "Menu.h"

int Menu::DatasetMenu() {
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

Menu::Menu() {

}


void Menu::MainMenu(Dataset dataset) {

    std::cout << "\n\n ----------------------------------------------\n"
                 "|                 Main Menu                    |\n"
                 " ----------------------------------------------\n";
    std::cout << "Hello, water supply manager!\n";
    std::cout << "Select the number of the topic...\n"
                 "[1]> Maximum Flow For City Water Distribution (2.1)\n"
                 "[2]> Maximum Flow Stats into a File\n"
                 "[3]> Water Sufficiency For Delivery Sites (2.2)\n"
                 "[4]> City Water Supply Impact from Individual Reservoir Failures (3.1)\n"
                 "[5]> Effect of Temporary Pumping Station Removal on Water Delivery (3.2)\n"
                 "[6]> Critical Pipeline Failures Impacting City Water Supply (3.3)\n"

                 "\n[0]> Quit\n";

    int topic_in_main_menu;
    std::string striTemp;
    Graph graph = dataset.getNetwork();


    double maxFlow = edmondsKarp(&graph,"SUPER_SOURCE","SUPER_SINK");

    while (!exit) {
        topic_in_main_menu = 0;
        striTemp = "";
        std::cin >> striTemp;
        try {
            topic_in_main_menu = stoi(striTemp);
        }
        catch (...) {
            topic_in_main_menu = 100;
        }

        if (topic_in_main_menu == 1) {
            std::string reservoir;
            int flow = 0;
            Node *foundReservoir = nullptr;

            while(foundReservoir == nullptr) {
                std::cout << "Enter reservoir code (Ex.: R_1): " << "\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input from previous input
                std::getline(std::cin, reservoir);

                foundReservoir = graph.findNode(reservoir);
            }

            for(auto pipe : foundReservoir->getPipes()) {
                flow += pipe->getFlow();
            }

            std::cout << "The maximum amount of water that goes though " + reservoir + " is " + std::to_string(flow) << '\n';
            std::cout << "The maximum flow of the graph is " + std::to_string(maxFlow) << '\n'; // TODO

            backToMainMenu();
        }
        else if(topic_in_main_menu == 2) {
            dumpMaxFlowFile();
            std::cout << "File dumped." << '\n';
            backToMainMenu();
        }
        else if (topic_in_main_menu == 3) {
            std::cout << "Not yet implemented" << '\n';
            backToMainMenu();
        }
        else if (topic_in_main_menu == 4) {

            std::string reservoir;
            int flow = 0;
            Node *foundReservoir = nullptr;

            while(foundReservoir == nullptr) {
                std::cout << "Enter reservoir code (Ex.: R_1): " << "\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input from previous input
                std::getline(std::cin, reservoir);

                foundReservoir = graph.findNode(reservoir);
            }

            removeNode(dataset, reservoir);

            backToMainMenu();
        }
        else if (topic_in_main_menu == 5) {
            std::cout << "Not yet implemented" << '\n';
            backToMainMenu();
        }
        else if (topic_in_main_menu == 6) {
            std::string city;
            int flow = 0;
            Node *foundCity = nullptr;

            while(foundCity == nullptr) {
                std::cout << "Enter city code (Ex.: C_1): " << "\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input from previous input
                std::getline(std::cin, city);

                foundCity = graph.findNode(city);
            }

            for(auto pipe : foundCity->getPipes()) {
                flow += pipe->getFlow();
            }
            backToMainMenu();
        }
        else if (topic_in_main_menu == 0) break;
        else std::cout << "Error: Choose one number of the Main Menu.\n";
    }

}


void Menu::backToMainMenu() {
    std::cout << "\n[1]> Back to Main Menu.\n"
                 "[0]> Quit.\n";
    int back;
    std::string striBack;
    while (true) {
        back = 0;
        striBack = "";
        std::cin >> striBack;
        try {
            back = stoi(striBack);
        }
        catch (...) {
            back = 10;
        }
        if (back == 1) MainMenu(dataset);
        else if (back == 0) { exit = true; break; }
        std::cout << "> Invalid choice.\n"
                     "[1]> Back to Main Menu.\n"
                     "[0]> Quit.\n";
    }
}

void Menu::dumpMaxFlowFile() {
    std::ofstream output("../maxFlowOutput.txt");
    std::vector<std::pair<std::string,int>> maxFlowCity;
    Graph graph = dataset->getNetwork();
    double maxFlow = edmondsKarp(&graph,"SUPER_SOURCE","SUPER_SINK");
    for(auto node : graph.getNodeSet()) {
        int currentFlow = 0;
        for(auto pipe : node->getPipes()){
            currentFlow += pipe->getFlow();
        }
        maxFlowCity.push_back({node->getInfo()->getCode(),currentFlow});
    }
    output << "Max-Flow - " << maxFlow << "\r\n";
    for(auto p : maxFlowCity) {
        output << p.first << " - " << p.second << "\r\n";
    }
}


