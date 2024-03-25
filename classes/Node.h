#include <vector>

template <class T>
class Pipe;

template <class T>
class Node{
   private:
      T type;
      std::vector<Pipe<T> *> pipes;
      bool visited;
      bool processing;
      int inDegree;
      int num;
      int low;
      
      void addPipe(Node<T> *dest, double capacity);
      bool removePipe(Node<T> *dest);

   public:
      Node(T type);

      T getType() const;
      void setType(T type) const;

      bool isVisited() const;
      void setVisited(bool v);

      bool isProcessing() const;
      void setProcessing(bool p);

      int getInDegree() const;
      void setInDegree(int inDegree);

      void setLow(int low);
      void setNum(int num);

      int getNum() const;
      int getLow() const;

      std::vector<Pipe<T> *> getPipes() const;
      void setPipes(const std::vector<Pipe<T>*> pipes);

};