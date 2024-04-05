#include "vector"
#include "string"
#include "Dataset.h"
#include "City.h"
#include <iostream>
#include <algorithm>
#include <complex>


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

    std::cout << "Variance: " << std::sqrt(calculate_variance(deficits)) << '\n';
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

    std::cout << "Variance: " << std::sqrt(calculate_variance(deficits)) << '\n';
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