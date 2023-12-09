//
// Created by simeo on 02.12.2023.
//

#include "Layer.h"

Layer::Layer(int inputSize, int neuronCount) {
    neurons.resize(neuronCount);
    for(auto& neuron : neurons) {
        neuron.weights.resize(inputSize);
    }
    init_weights();
}

void Layer::calc_neuron_outputs(const std::vector<double> &inputs) {
    for (size_t i = 0; i < neurons.size(); ++i) {
        neurons[i].calc_out(inputs);
    }
}

std::vector<double> Layer::get_neuron_outputs() {
    std::vector<double> outputs;
    outputs.resize(neurons.size());
    for (const auto& neuron : neurons) {
        outputs.push_back(neuron.out);
    }
    return outputs;
}

void Layer::update_weights(const std::vector<double> &inputs, std::vector<double> &deltas, double learningRate) {
    for (size_t i = 0; i < neurons.size(); ++i) {
        for (size_t j = 0; j < neurons[i].weights.size(); ++j) {
            neurons[i].weights[j] += learningRate * deltas[i] * inputs[j];
        }
    }
}

void Layer::init_weights() {
    srand(static_cast<unsigned>(time(0)));
    for(auto& neuron : neurons) {
        for (double & j : neuron.weights) {
            j = (rand() % 2000 - 1000) / 1000.0;  // Random values between -1 and 1
        }
    }
}
