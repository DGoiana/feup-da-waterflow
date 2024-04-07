//
// Created by ritac on 25/03/2024.
//

#include "Menu.h"
#include "Utils.h"

bool done = false;

void Menu::MainMenu() {

    auto graph = dataset.getNetwork();
    dataset.prepareSuperNodes();

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
                 "[7]> Balance Network (2.3)\n"

                 "\n[0]> Quit\n";

    int topic_in_main_menu;
    std::string striTemp;

    while (!done) {
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

                foundReservoir = dataset.getNetwork().findNode(reservoir);
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
            auto cityDeficits = deficitCities;
            for(auto element : cityDeficits) {
                auto code = element.first->getInfo()->getCode();
                auto maxDemand = dynamic_cast<City*>(element.first->getInfo())->getDeliveryDemand();
                if(element.second != 0) {
                    std::cout << code << " has deficit of " << element.second << '.';
                } else {
                    std::cout << code << " has no deficit.";
                }
                std::cout << " (Max Demand: " << maxDemand << ")" << '\n';
            }
            std::cout << "\n";
            showStatisticsDeficit(cityDeficits,0);
            backToMainMenu();
        }
        else if (topic_in_main_menu == 4) {

            std::string reservoir;
            Node *foundReservoir = nullptr;

            while(foundReservoir == nullptr) {
                std::cout << "Enter reservoir code (Ex.: R_1): " << "\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input from previous input
                std::getline(std::cin, reservoir);

                foundReservoir = graph.findNode(reservoir);
            }

            removeNode(&dataset, reservoir);

            backToMainMenu();
        }
        else if (topic_in_main_menu == 5) {

            for (Node* node : graph.getNodeSet()) {
                NetworkPoint* info = node->getInfo();
                std::string code = info->getCode();
                if (code[0]=='P'){
                    std::cout << "By removing the " << code  <<  " station: " << '\n';
                    removeNode(&dataset, code);
                }
            }

            backToMainMenu();
        }
        else if (topic_in_main_menu == 6) {
            std::string choice;
            int a;
            std::cout << "Choose:\n"
                         "0 - Pipes connected to Cities\n"
                         "1 - Remove singular pipe\n";
            std::cin >> choice;
            try {
                a = stoi(choice);
            } catch (...){backToMainMenu();}
            if(a == 0) {
                for(auto node: dataset.getNetwork().getNodeSet()) {
                    for(auto pipe: node->getPipes()) {
                        auto orig = pipe->getOrig()->getInfo()->getCode();
                        auto dest = pipe->getDest()->getInfo()->getCode();
                        std::cout <<"Removing " <<  orig << " -> " << dest << '\n';
                        removePipe(&dataset,orig,dest);
                        std::cout << '\n';
                    }
                }
            } else if (a == 1){
                std::string orig;
                std::string dest;
                Pipe *foundPipe = nullptr;

                while(foundPipe == nullptr) {
                    std::cout << "Enter reservoir code (Ex.: R_1): " << "\n";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input from previous input
                    std::cout << "Origin:\n";
                    std::getline(std::cin, orig);
                    std::cout << "Destination:\n";
                    std::getline(std::cin,dest);

                    foundPipe = graph.findPipe(orig,dest);
                }

                removePipe(&dataset, foundPipe->getOrig()->getInfo()->getCode(),foundPipe->getDest()->getInfo()->getCode());
            }
            backToMainMenu();
        }
        else if (topic_in_main_menu == 7) {
            auto newDataSet = dataset;
            newDataSet.prepareSuperNodes();
            balanceNetwork(&newDataSet);
            auto def = deficitCities;
            showStatisticsDeficit(def,0);
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
    while (!done) {
        back = 0;
        striBack = "";
        std::cin >> striBack;
        try {
            back = stoi(striBack);
        }
        catch (...) {
            back = 10;
        }
        if (back == 1) MainMenu();
        else if (back == 0) { done = true; break; }
        std::cout << "> Invalid choice.\n"
                     "[1]> Back to Main Menu.\n"
                     "[0]> Quit.\n";
    }
}

void Menu::dumpMaxFlowFile() {
    std::ofstream output("../maxFlowOutput.txt");
    std::vector<std::pair<std::string,int>> maxFlowCity;
    dataset.prepareSuperNodes();
    Graph graph = dataset.getNetwork();
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


