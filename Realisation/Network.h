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
#include <functional>

class Network {
public:
    Network(int in_size, int out_size, std::vector<int> layers_sizes);
    void train(std::vector<std::vector<double>> &inputs, std::vector<std::vector<double>> &labels, int epochs, double learning_rate, std::function <void (int, int)> cb_progress = nullptr,std::function <void (double)> cb_error = nullptr );
    double verify(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& labels, std::function <void (int, int)> cb_progress = nullptr);
    int predict(const std::vector<double>& input);
    std::vector<double> forward_propagation(const std::vector<double>& input);
    double backward_propagation(const std::vector<double>& target, double learning_rate);

private:
    std::vector<Layer> layers;
};

#endif //REALISATION_NETWORK_H
