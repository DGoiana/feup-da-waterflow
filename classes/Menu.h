//
// Created by ritac on 25/03/2024.
//

#ifndef FEUP_DA_PROJ1_MENU_H
#define FEUP_DA_PROJ1_MENU_H

#include <iostream>
#include <algorithm>
#include <limits>
#include "Dataset.h"
#include "Edmonds_Karps.h"
#include <fstream>
#include "Utils.h"

class Menu {
    bool exit = false;
    Dataset dataset;
    std::vector<std::pair<Node *,int>> deficitCities;
    std::vector<std::pair<Pipe *,int>> deficitPipes;
    double maxFlow;
    void backToMainMenu();

public:
    Menu(Dataset dataset) : dataset(dataset) {
        dataset.prepareSuperNodes();
        Graph graph = dataset.getNetwork();
        maxFlow = edmondsKarp(&graph,"SUPER_SOURCE","SUPER_SINK");
        deficitCities = createDeficitsCities(dataset.getNetwork());
        deficitPipes = createDeficitsPipes(dataset.getNetwork());
    };

    void MainMenu();


    void dumpMaxFlowFile();
};


#endif //FEUP_DA_PROJ1_MENU_H
