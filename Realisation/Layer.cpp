//
// Created by simeo on 02.12.2023.
//

#include "Layer.h"

Layer::Layer(int inputSize, int neuronCount) {
    neurons.resize(neuronCount);
    weights.resize(neuronCount, std::vector<double>(inputSize));
}

void Layer::calc_neuron_outputs(std::vector<double> &inputs) {
    for (size_t i = 0; i < neurons.size(); ++i) {
        neurons[i].calc_out(inputs, weights[i]);
    }
}
