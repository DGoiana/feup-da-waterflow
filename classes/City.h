#ifndef CITY_H_
#define CITY_H_

#include <string>
#include "NetworkPoint.h"

class City : public NetworkPoint {
   private:
      std::string name;
      int population;
      int deliveryDemand;
   public:
      City(std::string _name, std::string _code, int _id, int _deliveryDemand, int _population) : NetworkPoint(_code, _id), name(_name), population(_population), deliveryDemand(_deliveryDemand) {};
      int getDeliveryDemand() const { return this->deliveryDemand; }
      int getPopulation() const { return this->population; }
      std::string getName() const { return this->name; }
};

#endif