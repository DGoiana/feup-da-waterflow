#include "vector"
#include "string"
#include "Dataset.h"
#include "City.h"
#include "Edmonds_Karps.h"
#include "Parser.h"
#include <iostream>
#include <algorithm>
#include <complex>

/**
 * @file Utils.h
 * @brief Auxiliary Functions
 */

/**
 * @brief Creates the dataset for Madeira
 * @return The created dataset
 */
Dataset createSmallDataset();

/**
 * @brief Creates the dataset for Continental Portugal
 * @return The created dataset
 */
Dataset createLargeDataset();

/**
 * @file Utils.h
 * Calculates the variance for a vector of pipes and their deficits
 * @param data
 * @return Final variance value of an array of pipes' deficits
 */
double calculate_variance(const std::vector<std::pair<Pipe *, int>>& data);

/**
 * Calculates the variance for a vector of nodes and their deficits
 * @param data
 * @return Final variance value of an array of nodes' deficits
 */
double calculate_variance(const std::vector<std::pair<Node *, int>>& data);


/**
 * Show Statistics for the pipes (based on their deficit)
 * @param deficits array of pipes' deficits
 * @param maxFlow Max flow of the graph
 */
void showStatisticsDeficit(std::vector<std::pair<Pipe *,int>> deficits, double maxFlow);


/**
 * @file Utils.h
 * Show Statistics for the nodes (based on their deficit)
 * @param deficits array of nodes' deficits
 * @param maxFlow Max flow of the graph
 */
void showStatisticsDeficit(std::vector<std::pair<Node *,int>> deficits, double maxFlow);

/**
 * Creates the deficit array for Pipes
 * @param dataset dataset that has the graph
 * @return the array of pipes' deficits
 */
std::vector<std::pair<Pipe *,int>> createDeficitsPipes(Dataset dataset);

/**
 * Creates the deficit array for Cities (Nodes)
 * @param dataset dataset that has the graph
 * @return the array of Cities' deficits
 */
std::vector<std::pair<Node *,int>> createDeficitsCities(Dataset dataset);

/**
 * Removes a node from the graph (Reservoir, City or Station)
 *
 * Time Complexity: O(VE)
 * @param dataset dataset that contains graph
 * @param code code of the node to be deleted
 */
void removeNode(Dataset *dataset, std::string code);

/**
 * Removes a pipe from the graph
 *
 * Time Complexity: O(VE)
 * @param dataset dataset that contains graph
 * @param code code of the pipe to be deleted
 */
void removePipe(Dataset *dataset, std::string source, std::string dest);