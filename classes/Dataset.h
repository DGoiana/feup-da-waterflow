#ifndef DATASET_H_
#define DATASET_H_

#include "Graph.h"
#include <list>

class Dataset {
   private:
    Graph network;
   public:
    Dataset();
    Dataset(std::list<std::vector<std::string> > cities, std::list<std::vector<std::string> > pipes, std::list<std::vector<std::string> > stations, std::list<std::vector<std::string> > reservoirs);

    void loadCities(std::list<std::vector<std::string> > cities);
    void loadReservoirs(std::list<std::vector<std::string> > reservoirs);
    void loadStations(std::list<std::vector<std::string> > stations);
    void loadPipes(std::list<std::vector<std::string> > pipes);

    /**
     * @brief Creates and prepares the super nodes
     *
     * First, creates a super source and connects all the reservoir to it. Then creates a super sink and connects it to
     * all of the cities. This is to prepare for the Max-Flow algorithm, since for problems with various sources and
     * sinks, this seems to be the best solution.\n\n
     *
     * Time Complexity: O(V)
     */
    void prepareSuperNodes();
    Graph getNetwork() const;
};

#endif