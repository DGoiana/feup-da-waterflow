template <class T>
class Node;

template <class T>
class Pipe {
   private:
      Node<T>* dest;      // destination vertex
      double capacity;         // pipe capacity
   public:
      Pipe(Node<T> *d, double w);
      Node<T>* getDest() const;
      void setDest(Node<T> *dest);
      double getCapacity() const;
      void setCapacity(double capacity);

};