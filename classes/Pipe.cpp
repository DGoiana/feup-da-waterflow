#include "Pipe.h"

template <class T>
Pipe<T>::Pipe(Node<T> *d, double c){
   this->dest = d;
   this->capacity = c;
}

template <class T>
Node<T>* Pipe<T>::getDest() const { return this->dest; }

template <class T>
void Pipe<T>::setDest(Node<T> *dest) { this->dest = dest; };

template <class T>
double Pipe<T>::getCapacity() const { return this->capacity; };

template <class T>
void Pipe<T>::setCapacity(double capacity) { this->capacity = capacity; };