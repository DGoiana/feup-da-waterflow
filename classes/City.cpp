#include "City.h"

City::City(std::string name, std::string code, int id, int deliveryDemand, int population){
   this->name = name;
   this->code = code;
   this->id = id;
   this->population = population;
   this->deliveryDemand = deliveryDemand;
}

int City::getDeliveryDemand() const { return this->deliveryDemand; }
int City::getPopulation() const { return this->population; }
std::string City::getName() const { return this->name; }
std::string City::getCode() const { return this->code; }
int City::getID() const { return this->id; }