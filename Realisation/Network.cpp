//
// Created by simeo on 03.12.2023.
//

#include "Network.h"

Network::Network() {
    load_weights("weights_input.txt", input_layer.weights);
    for (size_t i = 0; i < hidden_layers.size(); ++i) {
        load_weights("weights_hidden_" + std::to_string(i) + ".txt", hidden_layers[i].weights);
    }
    load_weights("weights_output.txt", output_layer.weights);
}

void Network::add_hidden_layer(int neuron_count) {

}

void Network::train(std::vector<std::vector<double>> &inputs, std::vector<std::vector<double>> &labels, int epochs, double learningRate) {

}

double Network::verify(std::vector<std::vector<double>> &inputs, std::vector<std::vector<double>> &labels) {
    return 0;
}

int Network::predict(std::vector<double> &input) {
    return 0;
}

void Network::save_weights(const std::string &filename) {

}

void Network::load_weights(const std::string &filename, std::vector<std::vector<double>>& weights) {

}
