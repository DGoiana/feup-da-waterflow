#include <string>

class Reservoir {
   private:
      std::string name;
      std::string municipality;
      std::string code;
      int id;
      int maxDelivery;
   public:
      Reservoir(std::string name, std::string municipality, std::string code, int id, int maxDelivery);
      std::string getName() const;
      std::string getMunicipality() const;
      std::string getCode() const;
      int getID() const;
      int getMaxDelivery() const;
};