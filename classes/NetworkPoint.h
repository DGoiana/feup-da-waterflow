#ifndef NETWORK_POINT_H_
#define NETWORK_POINT_H_

#include <string>
/**
 * @brief SuperClass to all the different kinds of nodes present in the graph\n
 *
 * Pumping Station: where the flow goes through.\n
 * Reservoir: Nodes where the flow begins (a source).\n
 * City: Nodes where the flow ends (a sink).\n
 *
 */
class NetworkPoint{
   private:
      std::string code;
      int id;
   public:
      NetworkPoint() {};
      NetworkPoint(std::string _code, int _id) : code(_code), id(_id) {};

      virtual std::string getCode() const { return this->code; }
      virtual int getID() const { return this->id; }

      bool operator==(const NetworkPoint &other) const {
        return this->code == other.code;
      }
};

#endif