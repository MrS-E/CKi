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
#include<fstream>

class Network {
public:
    Network() : in_size(0), out_size(0), input_layer(0,0), output_layer(0,0) {};
    void add_hidden_layer(int neuron_count);
    void add_input_layer(int neuron_count);
    void add_output_layer(int neuron_count);
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

class NetworkBuilder {
public:
    NetworkBuilder()= default;
    void add_hidden_layer(int neuron_count);
    void add_input_layer(int neuron_count);
    void add_output_layer(int neuron_count);
    std::vector<int> lookup_sizes();
    void printout();
    Network build();
private:
    int in_size;
    int out_size;
    std::vector<int> hidden_sizes;
};


#endif //REALISATION_NETWORK_H
