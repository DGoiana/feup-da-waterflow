#include <unordered_map>
#include "Node.h"

template <class T>
class Graph {
   private:
	   std::unordered_map<string, Node<T>*> nodes;
   public:
      Graph();
      Graph(std::unordered_map<string, Node<T>*> nodes);

      // to implement
      Node<T>* findNode(const T &in) const;
      int getNumNode() const;
      
      // to implement
      bool addNode(const T &type);
      bool removeNode(const T &type);

      vector<Node<T>*> getNodeSet() const;

      // to implement
      vector<T> dfs() const;
      vector<T> dfs(const T & source) const;
      void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
      vector<T> bfs(const T &source) const;
};