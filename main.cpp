#include "Graph.h"
#include <iostream>

void testGraphBasicFunctions();
int main() {
    testGraphBasicFunctions();
}

void testGraphBasicFunctions() {
    Graph<int> graph;
    graph.addNode("Madeira",1); graph.addNode("Lisboa",2);
    graph.addNode("Porto",3); graph.addNode("Viseu",4);
    graph.addNode("Leça",5); graph.addNode("Faro",6);

    graph.addPipe(3,2,1); graph.addPipe(2,3,2);
    graph.addPipe(1,4,3); graph.addPipe(1,3,23);

    graph.addPipe(1,6,1); graph.addPipe(2,6,2);

    graph.removeNode(6);

    graph.addBidirectionalPipe(1,2,3);
    
}