//
// Created by simeo on 03.12.2023.
//

#ifndef REALISATION_NETWORK_H
#define REALISATION_NETWORK_H

#include<vector>
#include"Layer.h"
#include<string>

class Network {
public:
    Network();
    void add_hidden_layer(int neuron_count);
    void train(std::vector<std::vector<double>>& inputs, std::vector<std::vector<double>>& labels, int epochs, double learningRate);
    double verify(std::vector<std::vector<double>>& inputs, std::vector<std::vector<double>>& labels);
    int predict(std::vector<double>& input);
    void save_weights(const std::string& filename);
    void load_weights(const std::string& filename);

private:
    Layer input_layer;
    std::vector<Layer> hiddenLayers;
    Layer output_layer;
};


#endif //REALISATION_NETWORK_H
