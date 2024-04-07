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
    void backToMainMenu();

public:
    Menu();
    void MainMenu(Dataset dataset);

    int DatasetMenu();

    void dumpMaxFlowFile();
};


#endif //FEUP_DA_PROJ1_MENU_H
