#include "vector"
#include "string"
#include "City.h"
#include <iostream>
#include <algorithm>
#include <complex>


double calculate_variance(const std::vector<std::pair<std::string, int>>& data) {
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

void showStatisticsDeficit(std::vector<std::pair<std::string,int>> deficits, double maxFlow) {
    std::cout << "Deficit Stats" << '\n';

    for(auto d : deficits) {
        std::cout << d.first << " " << d.second << '\n';
    }

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

std::vector<std::pair<std::string,int>> createDeficits(Dataset dataset) {
    std::vector<std::pair<std::string,int>> deficitCities;

    for(Node *node: dataset.getNetwork().getNodeSet()) {
        if(node->getInfo()->getCode().substr(0,1) == "C") {
            double sumFlow = 0;
            double cityDemand = dynamic_cast<City*>(node->getInfo())->getDeliveryDemand();

            for(Pipe *p: node->getPipes()) {
                sumFlow += p->getFlow();
            }
            if(node->getInfo()->getCode().substr(0,1) == "C")
                deficitCities.push_back({node->getInfo()->getCode(),cityDemand - sumFlow});
        }
    }
    return deficitCities;
}