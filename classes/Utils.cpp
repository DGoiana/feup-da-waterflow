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

std::vector<std::pair<Pipe *,int>> createDeficitsPipes(Dataset dataset) {
    std::vector<std::pair<Pipe *,int>> deficitPipes;
    int index = 0;
    for(auto node : dataset.getNetwork().getNodeSet()) {
        for(Pipe *pipe: node->getPipes()) {
            deficitPipes.push_back({pipe,pipe->getCapacity() - pipe->getFlow()});
            index++;
        }
    }
    return deficitPipes;
}

std::vector<std::pair<Node *,int>> createDeficitsCities(Dataset dataset) {
    std::vector<std::pair<Node *,int>> deficitCities;
    for(auto node: dataset.getNetwork().getNodeSet()) {
        int sumFlow = 0;
        for(Pipe *pipe: node->getPipes()) {
            sumFlow += pipe->getFlow();
        }
        if(node->getInfo()->getCode().substr(0,1) == "C") {
            double cityDemand = dynamic_cast<City*>(node->getInfo())->getDeliveryDemand();
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
    std::vector<std::pair<Node*, int>> initialDeficits = createDeficitsCities(*dataset); // create initial deficits

    _graph.removeNode(*nodeToRemove->getInfo()); // remove node

    edmondsKarp(&_graph, "SUPER_SOURCE", "SUPER_SINK"); // run updated flow
    std::vector<std::pair<Node*, int>> finalDeficits = createDeficitsCities(*dataset); // create updated deficits

    
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
    std::vector<std::pair<Node*, int>> initialDeficits = createDeficitsCities(*dataset);

    Pipe* _pipe1 = _graph.findPipe(source, dest);
    Pipe* _pipe2 = _graph.findPipe(dest, source);

    if(_pipe1 != nullptr) _graph.removePipe(source, dest);
    if(_pipe2 != nullptr) _graph.removePipe(dest, source);

    edmondsKarp(&_graph, "SUPER_SOURCE", "SUPER_SINK");
    std::vector<std::pair<Node*, int>> finalDeficits = createDeficitsCities(*dataset);

    for(int i = 0; i < initialDeficits.size(); i++){
        if(initialDeficits[i].second != finalDeficits[i].second){
            std::cout << "The city " << dynamic_cast<City*>(initialDeficits[i].first->getInfo())->getName() << " (" << initialDeficits[i].first->getInfo()->getCode() <<  ") has changed it's deficit from " << initialDeficits[i].second << " to " << finalDeficits[i].second << '\n';
        }
    }

    if(_pipe1 != nullptr) _graph.addPipe(source, dest, _pipe1->getCapacity());
    if(_pipe2 != nullptr) _graph.addPipe(dest, source, _pipe2->getCapacity());
}