#ifndef FEUP_DA_PROJ1_EDMONDS_KARPS_H
#define FEUP_DA_PROJ1_EDMONDS_KARPS_H

#include "Graph.h"

/**
 * @file Edmonds_Karps.h
 * @brief Edmonds Karp Implementation
 */

/**
 * @brief Edmonds Karp Algorithm to determine a graph's Max-Flow
 *
 * The algorithm finds a path from the source and the target using a BFS, then it augments the path, creating a new
 * residual graph, after that it finds the minimum flow following that path and stores it which will contribute to the
 * final Max-Flow value. With the min-flow value and the new augmented graph, the algorithms is ready for the next
 * iteration. Those steps are repeated until there is no path between the source node and the target node.\n\n
 * Time Complexity: E(VE²)
 *
 * @param g Graph to be analyzed
 * @param source Source Node identification code
 * @param dest Destination Node identification code
 * @return Max-Flow value
 */
float edmondsKarp(Graph *g, std::string source, std::string dest);

/**
 * @brief BFS to find path between source and target
 *
 * The BFS algorithm is used to find the shortest path between the source node and the target node, if it does not find
 * a path, then return false.
 *
 * @param g Graph to be analyzed
 * @param s Source Node
 * @param t Target Node
 * @return if there is a path between source and target
 */
bool findPath(Graph *g,Node *s,Node *t);

/**
 * @brief Augments the graph using the min-flow
 *
 * This auxiliary function determines the augmented path using the minimum flow in the path. The new nodes
 * in the augmented graph are created in the reserved direction of the nodes present in the path with the capacity of
 * the min-flow.
 *
 * @param s Source Node
 * @param t Target Node
 * @param minFlow Minimum-Flow value
 */
void augmentGraph(Node *s, Node *t,float minFlow);

/**
 * @brief Determines the minimum flow in a path
 *
 * Given the target node, the function iterates through the nodes via the "path" attribute until it finds the source
 * node. While transversing the path, it checks for the minimum-value of flow in those nodes. At the end, it returns
 * the min-flow value.
 *
 * @param s Source Node
 * @param t Target Node
 * @return Minimum-Flow value
 */
float getMinFlow(Node *s, Node *t);

#endif //FEUP_DA_PROJ1_EDMONDS_KARPS_H
