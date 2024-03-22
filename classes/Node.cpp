#include "Node.h"
#include <vector>

template <class T>
Node<T>::Node(T type) {
   this->type = type;
}

template <class T>
T Node<T>::getType() const { return type; }

template <class T>
void Node<T>::setType(T type) const { this->type = type; }

template <class T>
bool Node<T>::isVisited() const { return visited; };

template <class T>
void Node<T>::setVisited(bool v) { this->visited = v};

template <class T>
bool Node<T>::isProcessing() const { return this->processing; }

template <class T>
void Node<T>::setProcessing(bool p) { this->processing = p; };

template <class T>
int Node<T>::getInDegree() const { return this->inDegree; }

template <class T>
void Node<T>::setInDegree(int inDegree) { this->inDegree = inDegree; }

template <class T>
void Node<T>::setLow(int low) { this->low = low; };

template <class T>
void Node<T>::setNum(int num) { this->num = num; };

template <class T>
int Node<T>::getNum() const { return this->num; }

template <class T>
int Node<T>::getLow() const { return this->low; }

template <class T>
std::vector<Pipe<T>*> Node<T>::getPipes() const { return this->pipes }

template <class T>
void Node<T>::setPipes(const std::vector<Pipe<T>*> pipes) { this.pipes = pipes; }