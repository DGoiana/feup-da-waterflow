#include "Reservoir.h"

Reservoir::Reservoir(std::string name, std::string municipality, std::string code, int id, int maxDelivery){
   this->name = name;
   this->code = code;
   this->id = id;
   this->municipality = municipality;
   this->maxDelivery = maxDelivery;
}

int Reservoir::getMaxDelivery() const { return this->maxDelivery; }
std::string Reservoir::getMunicipality() const { return this->municipality; }
std::string Reservoir::getName() const { return this->name; }
std::string Reservoir::getCode() const { return this->code; }
int Reservoir::getID() const { return this->id; }