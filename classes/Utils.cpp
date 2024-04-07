#include "Utils.h"


Dataset createSmallDataset() {
    Parser parser;

    std::list<std::vector<std::string> > cities = parser.parseCities("../small_dataset/Cities_Madeira.csv");
    std::list<std::vector<std::string> > reservoirs = parser.readFile("../small_dataset/Reservoirs_Madeira.csv");
    std::list<std::vector<std::string> > stations = parser.readFile("../small_dataset/Stations_Madeira.csv");
    stations.pop_back();
    std::list<std::vector<std::string> > pipes = parser.readFile("../small_dataset/Pipes_Madeira.csv");

    return Dataset(cities, pipes, stations, reservoirs);
}

Dataset createLargeDataset() {
    Parser parser;

    std::list<std::vector<std::string> > cities = parser.parseCities("../large_dataset/Cities.csv");
    std::list<std::vector<std::string> > reservoirs = parser.readFile("../large_dataset/Reservoir.csv");
    std::list<std::vector<std::string> > stations = parser.readFile("../large_dataset/Stations.csv");
    std::list<std::vector<std::string> > pipes = parser.readFile("../large_dataset/Pipes.csv");

    return Dataset(cities, pipes, stations, reservoirs);
}

double calculate_variance(const std::vector<std::pair<Pipe *, int>>& data) {
    if (data.empty()) {
        return 0.0; // Return 0 if the input vector is empty
    }

    // Calculate mean
    double mean = 0.0;
    for (const auto& pair : data) {
        mean += pair.second;
    }
    mean /= data.size();

    // Calculate squared differences from the mean
    double squared_diff = 0.0;
    for (const auto& pair : data) {
        squared_diff += std::pow(pair.second - mean, 2);
    }

    // Calculate variance
    double variance = squared_diff / data.size();
    return variance;
}

double calculate_variance(const std::vector<std::pair<Node *, int>>& data) {
    if (data.empty()) {
        return 0.0; // Return 0 if the input vector is empty
    }

    // Calculate mean
    double mean = 0.0;
    for (const auto& pair : data) {
        mean += pair.second;
    }
    mean /= data.size();

    // Calculate squared differences from the mean
    double squared_diff = 0.0;
    for (const auto& pair : data) {
        squared_diff += std::pow(pair.second - mean, 2);
    }

    // Calculate variance
    double variance = squared_diff / data.size();
    return variance;
}

void showStatisticsDeficit(std::vector<std::pair<Pipe *,int>> deficits, double maxFlow) {
    for(auto p: deficits) {
        auto pipe = p.first;
        std::cout << pipe->getOrig()->getInfo()->getCode() << " -> " << pipe->getDest()->getInfo()->getCode() << '\n';
        std::cout << "   Demand: " <<  pipe->getCapacity() << '\n';
        std::cout << "   Actual Flow: " << pipe->getFlow() << '\n';
        std::cout << "   Deficit: " << pipe->getCapacity() - pipe->getFlow() << '\n';    }

    std::cout << "Deficit Stats" << '\n';

    std::cout << "Variance: " << calculate_variance(deficits) << '\n';
    // Calculate mean
    double mean = 0.0;
    for (const auto &pair: deficits) {
        mean += pair.second;
    }
    mean /= deficits.size();

    std::cout << "Mean: " << mean << '\n';
    auto maxDiff = *(std::max_element(deficits.begin(), deficits.end(),
                                      [](auto a, auto b) { return a.second < b.second; }));
    std::cout << "Max difference: " << maxDiff.second << '\n';
    std::cout << "Max flow: " << maxFlow << '\n';
}

void showStatisticsDeficit(std::vector<std::pair<Node *,int>> deficits, double maxFlow) {
    for(auto p : deficits) {
        auto node = p.first;
        int sumFlow = 0;
        for(Pipe *pipe: node->getPipes()) {
            sumFlow += pipe->getFlow();
        }
        if(node->getInfo()->getCode().substr(0,1) == "C") {
            double cityDemand = dynamic_cast<City*>(node->getInfo())->getDeliveryDemand();
            std::cout << node->getInfo()->getCode() << '\n';
            std::cout << "   Demand: " <<  cityDemand << '\n';
            std::cout << "   Actual Flow: " << sumFlow << '\n';
            std::cout << "   Deficit: " << cityDemand - sumFlow << '\n';
        }
    }

    std::cout << "Deficit Stats" << '\n';

    std::cout << "Variance: " << calculate_variance(deficits) << '\n';
    // Calculate mean
    double mean = 0.0;
    for (const auto &pair: deficits) {
        mean += pair.second;
    }
    mean /= deficits.size();

    std::cout << "Mean: " << mean << '\n';
    auto maxDiff = *(std::max_element(deficits.begin(), deficits.end(),
                                      [](auto a, auto b) { return a.second < b.second; }));
    std::cout << "Max difference: " << maxDiff.second << '\n';
}

std::vector<std::pair<Pipe *,int>> createDeficitsPipes(Graph _graph) {
    std::vector<std::pair<Pipe *,int>> deficitPipes;
    int index = 0;
    for(auto node : _graph.getNodeSet()) {
        for(Pipe *pipe: node->getPipes()) {
            deficitPipes.push_back({pipe,pipe->getCapacity() - pipe->getFlow()});
            index++;
        }
    }
    return deficitPipes;
}

std::vector<std::pair<Node *,int>> createDeficitsCities(Graph graph) {
    std::vector<std::pair<Node *,int>> deficitCities;
    for(auto node: graph.getNodeSet()) {
            int sumFlow = 0;
            for (Pipe *pipe: node->getPipes()) {
                sumFlow += pipe->getFlow();
            }
            if (node->getInfo()->getCode().substr(0, 1) == "C") {
                double cityDemand = dynamic_cast<City *>(node->getInfo())->getDeliveryDemand();
                deficitCities.push_back({node, cityDemand - sumFlow});
            }
    }
    return deficitCities;
}

void removeNode(Dataset *dataset, std::string code){
    Graph _graph = dataset->getNetwork(); // get graph

    Node* nodeToRemove = _graph.findNode(code); // find node to remove

    std::vector<Pipe*> oldOutgoingPipes = nodeToRemove->getPipes();
    std::vector<Pipe*> oldIncomingPipes = nodeToRemove->getIncoming();

    edmondsKarp(&_graph, "SUPER_SOURCE", "SUPER_SINK"); // run initial flow
    std::vector<std::pair<Node*, int>> initialDeficits = createDeficitsCities(_graph); // create initial deficits

    _graph.removeNode(*nodeToRemove->getInfo()); // remove node

    edmondsKarp(&_graph, "SUPER_SOURCE", "SUPER_SINK"); // run updated flow
    std::vector<std::pair<Node*, int>> finalDeficits = createDeficitsCities(_graph); // create updated deficits

    
    for(int i = 0; i < initialDeficits.size(); i++){
        if(initialDeficits[i].second != finalDeficits[i].second){
            std::cout << "The city " << dynamic_cast<City*>(initialDeficits[i].first->getInfo())->getName() << " (" << initialDeficits[i].first->getInfo()->getCode() <<  ") has changed it's deficit from " << initialDeficits[i].second << " to " << finalDeficits[i].second << '\n';
        }
    } 

    for(auto p: oldOutgoingPipes){
        nodeToRemove->addPipe(p->getDest(), p->getCapacity());
    }

    for(auto p: oldIncomingPipes){
        p->getOrig()->addPipe(nodeToRemove, p->getCapacity());
    }
}

void removePipe(Dataset *dataset, std::string source, std::string dest){
    Graph _graph = dataset->getNetwork();

    edmondsKarp(&_graph, "SUPER_SOURCE", "SUPER_SINK");
    std::vector<std::pair<Node*, int>> initialDeficits = createDeficitsCities(_graph);

    Pipe* _pipe1 = _graph.findPipe(source, dest);
    Pipe* _pipe2 = _graph.findPipe(dest, source);

    if(_pipe1 != nullptr) _graph.removePipe(source, dest);
    if(_pipe2 != nullptr) _graph.removePipe(dest, source);

    edmondsKarp(&_graph, "SUPER_SOURCE", "SUPER_SINK");
    std::vector<std::pair<Node*, int>> finalDeficits = createDeficitsCities(_graph);

    for(int i = 0; i < initialDeficits.size(); i++){
        if(initialDeficits[i].second != finalDeficits[i].second){
            std::cout << "The city " << dynamic_cast<City*>(initialDeficits[i].first->getInfo())->getName() << " (" << initialDeficits[i].first->getInfo()->getCode() <<  ") has changed it's deficit from " << initialDeficits[i].second << " to " << finalDeficits[i].second << '\n';
        }
    }

    if(_pipe1 != nullptr) _graph.addPipe(source, dest, _pipe1->getCapacity());
    if(_pipe2 != nullptr) _graph.addPipe(dest, source, _pipe2->getCapacity());
}

/**
 * @brief Balance pipes' flow
 *
 * This algorithm redistributes the flow in outgoing reservoirs pipes.
 * It calculates the mean of the outgoing flow and tries to redistribute the flow equally in all pipes.\n\n
 * @param reservoir to be balanced.
 */
void balanceNode(Node *n){
    double mean = 0;
    for (auto p: n->getPipes()) {
        mean += p->getFlow();
    }
    mean /= n->getPipes().size();

    std::vector<Pipe *> aboveAverage;
    std::vector<Pipe *> belowAverage;

    for (auto p: n->getPipes()) {
        if (p->getFlow() >= mean) aboveAverage.push_back(p);
        if (p->getFlow() < mean && p->getFlow() < p->getCapacity()) belowAverage.push_back(p);
    }

    double toDistribute = 0;

    for (auto p: aboveAverage) {
        toDistribute += p->getFlow() - mean;
        p->setFlow(p->getFlow() - (p->getFlow() - mean));
    }


    for (auto p: belowAverage) {
        if (toDistribute >= mean - p->getFlow() - 0.00001) {
            toDistribute -= std::min(p->getCapacity() - p->getFlow(), mean - p->getFlow());
            p->setFlow(std::min(p->getCapacity(), mean));
        }
    }

    if (toDistribute > 0) {
        std::vector<Pipe *> usablePipes;

        for (auto p: n->getPipes()) {
            if (p->getFlow() < p->getCapacity()) usablePipes.push_back(p);
        }

        sort(usablePipes.begin(), usablePipes.end(), [](Pipe *p1, Pipe *p2) {
            return p1->getCapacity() < p2->getCapacity();
        });

        for (auto p: usablePipes) {
            if (p->getFlow() + toDistribute > p->getCapacity()) {
                toDistribute -= p->getCapacity() - p->getFlow();
                p->setFlow(p->getCapacity());
            } else {
                p->setFlow(p->getFlow() + toDistribute);
            }
        }
    }
}

/**
 * @brief Balances the flow network
 *
 * This algorithm tries to balance the flow network. It decreases the flow variance as well as the max difference, with a slight
 * trade off with the max flow. It balances the reservoirs first and then it propagates the updated flow to the pumping stations.
 * \n\n
 *
 * Time Complexity: O(VE²)
 * @param dataset to be balanced.
 */
void balanceNetwork(Dataset *dataset){
    Graph _graph = dataset->getNetwork();

    edmondsKarp(&_graph, "SUPER_SOURCE", "SUPER_SINK");
    auto initialDeficits = createDeficitsPipes(_graph);

    for(auto n : _graph.getNodeSet()){
        if(n->getInfo()->getCode().substr(0, 1) == "R") balanceNode(n);
    }

    for(auto n : _graph.getNodeSet()){
        if(n->getInfo()->getCode().substr(0, 1) == "P"){
            double incomingFlow = 0;
            for(auto p: n->getIncoming()) incomingFlow += p->getFlow();
            for(auto p: n->getPipes()) p->setFlow(0);

            double mean = incomingFlow / n->getPipes().size();

            for(auto p: n->getPipes()){
                if(p->getCapacity() < mean){
                    p->setFlow(p->getCapacity());
                    incomingFlow -= p->getCapacity();
                }
                else{
                    p->setFlow(mean);
                    incomingFlow -= mean;
                }
            }

            if(incomingFlow > 0){
                std::vector<Pipe *> usablePipes;

                for (auto p: n->getPipes()) {
                    if (p->getFlow() < p->getCapacity()) usablePipes.push_back(p);
                }

                sort(usablePipes.begin(), usablePipes.end(), [](Pipe *p1, Pipe *p2) {
                    return p1->getCapacity() < p2->getCapacity();
                });

                for (auto p: usablePipes) {
                    if (p->getFlow() + incomingFlow > p->getCapacity()) {
                        incomingFlow -= p->getCapacity() - p->getFlow();
                        p->setFlow(p->getCapacity());
                    } else {
                        p->setFlow(p->getFlow() + incomingFlow);
                    }
                }
            }
        }
    }
}