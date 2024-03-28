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

      Graph getNetwork() const;
};

#endif