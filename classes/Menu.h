//
// Created by ritac on 25/03/2024.
//

#ifndef FEUP_DA_PROJ1_MENU_H
#define FEUP_DA_PROJ1_MENU_H


class Menu::Menu() {

    std::cout << "\n\n ----------------------------------------------\n"
                 "|                 Main Menu                    |\n"
                 " ----------------------------------------------\n";
        std::cout << "Hello, water supply manager!\n";
        std::cout << "Select the number of the topic...\n"
        "[1]> Maximum Flow For City Water Distribution (2.1)\n"
        "[2]> Water Sufficiency For Delivery Sites (2.2)\n"
        "[3]> Minimization Flow Capacity Differences (2.3)\n"
        "[4]> City Water Supply Impact from Individual Reservoir Failures (3.1)\n"
        "[5]> Effect of Temporary Pumping Station Removal on Water Delivery (3.2)\n"
        "[6]> Critical Pipeline Failures Impacting City Water Supply (3.3)\n"

        "\n[0]> Quit\n";

    int topic_in_main_menu;
    std::string striTemp;

    while (true) {
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
        auto itRes = ; // Initialize iterator to end

        while (itRes == data.Stations_Network.end()) {
        std::cout << "Enter reservoir: \n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input from previous input
        std::getline(std::cin, reservoir);

        //TODO: Change where it gets its data from
        itRes = std::find_if(data.Stations_Network.begin(), data.Stations_Network.end(),[&reservoir](Vertex *vertex) {
                               return reservoir == vertex->getName();
                           });
        }

        std::string deliverySite;
        auto itDeliv = data.Stations_Network.end(); // Initialize iterator to end

        while (itDeliv == data.Stations_Network.end()) {
        std::cout << "Enter delivery site: \n";
        std::getline(std::cin, deliverySite);

        //TODO: Change where it gets its data from
        itDeliv = std::find_if(data.Stations_Network.begin(), data.Stations_Network.end(),[&station2](Vertex *vertex) {
            return station2 == vertex->getName();
        });
        }

        //TODO: Change where it gets its data from
        /*call to function
        data_.graph.ResetGraphValues();
        double max = data_.graph.edmondskarp(*itRes, *itDeliv);
        */
        std::cout << "The maximum amount of water that can reach " + deliverySite + " from " +
        reservoir + " is " + std::to_string(max) + "\n";

        backToMainMenu();
    }
    else if (topic_in_main_menu == 2) {
        /* function that returns an array with all the cities that cant be supplied and the desired water rate value
            vector scarcityArray = exercise-2-2();
         */
        std::cout << "City " << " Water Rate Needed" <<  std::endl;

        for city in scarcityArray
            std::cout << scarcityArray.city[0] << "  " << scarcityArray.city[1] << std::endl;

        backToMainMenu();
    }
    else if (topic_in_main_menu == 3) {




        backToMainMenu();
    }
    else if (topic_in_main_menu == 4) {
        std::string reservoir;
        auto itRes = ; // Initialize iterator to end

        while (itRes == data.Stations_Network.end()) {
        std::cout << "Enter reservoir: \n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining input from previous input
        std::getline(std::cin, reservoir);

        //TODO: Change where it gets its data from
        itRes = std::find_if(data.Stations_Network.begin(), data.Stations_Network.end(),[&reservoir](Vertex *vertex) {
            return reservoir == vertex->getName();
        });
        }

        backToMainMenu();
        }
    else if (topic_in_main_menu == 5) {


    backToMainMenu();
    }
    else if (topic_in_main_menu == 6) {


    backToMainMenu();
    }
    else if (topic_in_main_menu == 0) break;
        else std::cout << "Error: Choose one number of the Main Menu.\n";
    }

};


void Menu::backToMainMenu( ){
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
        if (back == 1) Menu menu();
        else if (back == 0) break;
        std::cout << "> Invalid choice.\n"
                     "[1]> Back to Main Menu.\n"
                     "[0]> Quit.\n";
    }



#endif //FEUP_DA_PROJ1_MENU_H
