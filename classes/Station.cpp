#include "Station.h"

Station::Station(std::string code, int id){
   this->code = code;
   this->id = id;
}

std::string Station::getCode() const { return this->code; }
int Station::getID() const { return this->id; }