//
// Created by MrS-E on 03.12.2023.
//

#ifndef REALISATION_NETWORK_H
#define REALISATION_NETWORK_H

#include<vector>
#include"Layer.h"
#include<string>
#include<iostream>
#include <algorithm>
#include<fstream>

class Network {
public:
    Network(int in_size, int out_size, std::vector<int> layers_sizes);

    void train(std::vector<std::vector<double>> &inputs, std::vector<std::vector<double>> &labels, int epochs, double learning_rate);
    double verify(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& labels);
    int predict(const std::vector<double>& input);
    std::vector<double> forward_propagation(const std::vector<double>& input);
    void backward_propagation(const std::vector<double>& target, double learning_rate);

private:
    std::vector<Layer> layers;
};

#endif //REALISATION_NETWORK_H
