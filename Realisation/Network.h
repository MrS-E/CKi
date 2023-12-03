//
// Created by simeo on 03.12.2023.
//

#ifndef REALISATION_NETWORK_H
#define REALISATION_NETWORK_H

#include<vector>
#include"Layer.h"
#include<string>
#include<iostream>
#include <algorithm>

class Network {
public:
    Network(int in_size, int out_size);
    void add_hidden_layer(int neuron_count);
    void train(std::vector<std::vector<double>>& inputs, std::vector<std::vector<double>>& labels, int epochs, double learningRate);
    double verify(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& labels);
    int predict(std::vector<double>& input);
    void save_weights(const std::string& filename);
    void load_weights(const std::string& filename, std::vector<std::vector<double>>& weights);

private:
    int in_size;
    int out_size;
    Layer input_layer;
    std::vector<Layer> hidden_layers;
    Layer output_layer;
};


#endif //REALISATION_NETWORK_H
