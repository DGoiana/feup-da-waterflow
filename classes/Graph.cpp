#include "Graph.h"

Graph::Graph();

template <class T>
Graph<T>::Graph(std::unordered_map<string, Node<T>*> nodes){
   this->nodes = nodes;
}

template <class T>
vector<Node<T>*> getNodeSet() const { return this->nodes; };