#include "Dataset.h"
#include "City.h"
#include "Station.h"
#include "Reservoir.h"
#include <string>

Dataset::Dataset(){
   this->network = Graph();
}

Dataset::Dataset(std::list<std::vector<std::string> > cities, std::list<std::vector<std::string> > pipes, std::list<std::vector<std::string> > stations, std::list<std::vector<std::string> > reservoirs){
   loadCities(cities);
   loadReservoirs(reservoirs);
   loadStations(stations);
   loadPipes(pipes);
}

Graph Dataset::getNetwork() const { return this->network; }

void Dataset::loadCities(std::list<std::vector<std::string>> cities){
   for(std::vector<std::string> _city : cities){
      City city = City(_city[0], _city[2], stoi(_city[1]), stoi(_city[3]), stoi(_city[4]));
      network.addNode(_city[2], city);
   }
}

void Dataset::loadStations(std::list<std::vector<std::string>> stations){
   for(std::vector<std::string> _station : stations){
      Station station = Station(_station[1], stoi(_station[0]));
      network.addNode(_station[1], station);
   }
}

void Dataset::loadReservoirs(std::list<std::vector<std::string>> reservoirs){
   for(std::vector<std::string> _reservoir : reservoirs){
      Reservoir reservoir = Reservoir(_reservoir[0], _reservoir[1], _reservoir[3], stoi(_reservoir[2]), stoi(_reservoir[4]));
      network.addNode(_reservoir[3], reservoir);
   }
}

void Dataset::loadPipes(std::list<std::vector<std::string>> pipes){
   for(std::vector<std::string> _pipe : pipes){
      if(_pipe[3] == "1"){
         network.addBidirectionalPipe(_pipe[0],_pipe[1], stoi(_pipe[2]));
      }
      else{
         network.addPipe(_pipe[0],_pipe[1], stoi(_pipe[2]));
      }
   }
}

