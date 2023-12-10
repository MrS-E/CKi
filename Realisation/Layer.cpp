//
// Created by MrS-E on 02.12.2023.
//

#include "Layer.h"

Layer::Layer(int input_size, int neuron_count) {
    Layer::neurons.resize(neuron_count);
    for(auto& neuron : Layer::neurons) {
        neuron.weights.resize(input_size);
    }
    Layer::init_weights();
}

void Layer::init_weights() {
    srand(static_cast<unsigned>(time(0)));
    for(auto& neuron : Layer::neurons) {
        for (double & j : neuron.weights) {
            j = (rand() % 2000 - 1000) / 1000.0;
        }
    }
}

void Layer::set_weights(const std::vector<std::vector<double>> &weights) {
    for (std::size_t i = 0; i < Layer::neurons.size(); ++i) {
        Layer::neurons[i].weights = weights[i];
    }
}

void Layer::calc_neuron_outputs(const std::vector<double> &inputs) {
    for (auto & neuron : Layer::neurons) {
        neuron.calc_out(inputs);
    }
}

std::vector<double> Layer::get_neuron_outputs() {
    std::vector<double> outputs(Layer::neurons.size());
    for (std::size_t i = 0; i < Layer::neurons.size(); ++i)  {
        outputs[i] = Layer::neurons[i].out;
    }
    return outputs;
}

std::vector<double> Layer::forward_propagation(const std::vector<double>& inputs) {
    Layer::calc_neuron_outputs(inputs);
    return Layer::get_neuron_outputs();
}

