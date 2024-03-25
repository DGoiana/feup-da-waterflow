#include <unordered_map>
#include <vector>
#include <string>
#include "Node.h"

template <class T>
class Graph {
   private:
	   std::unordered_map<std::string, Node<T>*> nodes;
   public:
      Graph();
      Graph(std::unordered_map<std::string, Node<T>*> nodes);

      // to implement
      Node<T>* findNode(const T &in) const;
      int getNumNode() const;
      
      // to implement
      bool addNode(const T &type);
      bool removeNode(const T &type);

      std::vector<Node<T>*> getNodeSet() const;

      // to implement
      std::vector<T> dfs() const;
      std::vector<T> dfs(const T & source) const;
      void dfsVisit(Node<T> *v, std::vector<T> & res) const;
      std::vector<T> bfs(const T &source) const;
};