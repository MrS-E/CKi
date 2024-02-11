//
// Created by MrS-E on 03.12.2023.
//

#ifndef REALISATION_NETWORK_H
#define REALISATION_NETWORK_H

#include<vector>
#include"Layer.h"
#include<string>
#include<iostream>
#include<algorithm>
#include<fstream>
#include<nlohmann/json.hpp>

class Network {
public:
    Network(int in_size, int out_size, std::vector<int> layers_sizes);

    double train(std::vector<std::vector<double>> &inputs, std::vector<std::vector<double>> &labels, int epochs, double learning_rate);
    double verify(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& labels);
    int predict(const std::vector<double>& input);
    std::vector<double> forward_propagation(const std::vector<double>& input);
    double backward_propagation(const std::vector<double>& target, double learning_rate);
    void save_network(const std::string& filename);
    void load_network(const std::string& filename);

private:
    std::vector<Layer> layers;
};

#endif //REALISATION_NETWORK_H
