#include <string>

class City {
   private:
      std::string name;
      std::string code;
      int id;
      int population;
      int deliveryDemand;
   public:
      City(std::string name, std::string code, int id, int deliveryDemand, int population);
      std::string getName() const;
      std::string getCode() const;
      int getID() const;
      int getPopulation() const;
      int getDeliveryDemand() const;
};