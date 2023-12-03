//
// Created by simeo on 02.12.2023.
//

#include "Layer.h"

Layer::Layer(int inputSize, int neuronCount) {
    neurons.resize(neuronCount);
    weights.resize(neuronCount, std::vector<double>(inputSize));
}

void Layer::calc_neuron_outputs(const std::vector<double> &inputs) {
    for (size_t i = 0; i < neurons.size(); ++i) {
        neurons[i].calc_out(inputs, weights[i]);
    }
}

std::vector<double> Layer::get_neuron_outputs() {
    std::vector<double> outputs;
    outputs.reserve(neurons.size());
    for (const auto& neuron : neurons) {
        outputs.push_back(neuron.out);
    }
    return outputs;
}

void Layer::update_weights(const std::vector<double> &inputs, std::vector<double> &deltas, double learningRate) {
    for (size_t i = 0; i < neurons.size(); ++i) {
        for (size_t j = 0; j < weights[i].size(); ++j) {
            weights[i][j] += learningRate * deltas[i] * inputs[j];
        }
    }
}
