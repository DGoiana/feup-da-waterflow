#ifndef RESERVOIR_H_
#define RESERVOIR_H_

#include <string>
#include "NetworkPoint.h"

class Reservoir : public NetworkPoint {
   private:
      std::string name;
      std::string municipality;
      int maxDelivery;
   public:
      Reservoir(std::string _name, std::string _municipality, std::string _code, int _id, int _maxDelivery) : NetworkPoint(_code, _id), name(_name), municipality(_municipality), maxDelivery(_maxDelivery) {};
      
      int getMaxDelivery() const { return this->maxDelivery; }
      std::string getMunicipality() const { return this->municipality; }
      std::string getName() const { return this->name; }
};

#endif