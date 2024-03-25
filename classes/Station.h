#include <string>

class Station {
   private:
      std::string code;
      int id;
   public:
      Station(std::string code, int id);
      std::string getCode() const;
      int getID() const;
};