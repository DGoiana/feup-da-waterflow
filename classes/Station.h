#ifndef STATION_H_
#define STATION_H_

#include <string>
#include "NetworkPoint.h"

class Station : public NetworkPoint {
   public:
      Station(std::string _code, int _id) : NetworkPoint(_code, _id) {};
};

#endif