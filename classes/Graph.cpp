#include "Graph.h"

template <class T>
Graph<T>::Graph(std::unordered_map<std::string, Node<T>*> nodes){
   this->nodes = nodes;
}

template <class T>
std::vector<Node<T>*> Graph<T>::getNodeSet() const { return this->nodes; };