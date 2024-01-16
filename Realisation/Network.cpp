//
// Created by MrS-E on 03.12.2023.
//

#include "Network.h"

Network::Network(int in_size, int out_size, std::vector<int> hidden_layers_sizes) {
    Network::layers.emplace_back(1, in_size);
    for(auto& layer_size : hidden_layers_sizes) {
        Network::layers.emplace_back(in_size, layer_size);
        in_size = layer_size;
    }
    Network::layers.emplace_back(in_size, out_size);
}

int Network::predict(const std::vector<double> &input) {
    std::vector<double> outputs = Network::forward_propagation(input);
    return static_cast<int>(std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end())));
}

double Network::verify(const std::vector<std::vector<double>> &inputs, const std::vector<std::vector<double>> &labels) {
    int correct = 0;
    for (std::size_t i = 0; i < inputs.size(); ++i) {
        if (Network::predict(std::vector<double>(inputs[i])) == std::distance(labels[i].begin(), std::max_element(labels[i].begin(), labels[i].end()))) {
            correct++;
        }
    }
    return static_cast<double>(correct) / static_cast<double>(inputs.size());
}

void Network::train(std::vector<std::vector<double>> &inputs, std::vector<std::vector<double>> &labels, int epochs, double learning_rate) {
    for(int epoch = 0; epoch<epochs; epoch++ ){
        for(std::size_t i = 0; i < inputs.size(); ++i) {
            std::vector<double> outputs = Network::forward_propagation(inputs[i]);
            //add backpropagation
        }
    }
}
