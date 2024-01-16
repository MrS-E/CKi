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
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for(auto& neuron : Layer::neurons) {
        for (double & j : neuron.weights) {
            j = static_cast<double>((std::rand() % 2000 - 1000) / 1000.0);
        }
    }
}

void Layer::set_weights(const std::vector<std::vector<double>> &weights) {
    for (std::size_t i = 0; i < Layer::neurons.size(); ++i) {
        Layer::neurons[i].weights = weights[i];
    }
}

void Layer::calc_neuron_outputs(const std::vector<double> &inputs){
    for (auto & neuron : Layer::neurons) {
        neuron.calc_activation(inputs);
    }
}

std::vector<double> Layer::get_neuron_outputs()
{
    std::vector<double> outputs(Layer::neurons.size());
    for (std::size_t i = 0; i < Layer::neurons.size(); ++i)  {
        outputs[i] = Layer::neurons[i].activation;
    }
    return outputs;
}

void backward_propagation(const std::vector<double> &expected_output, const std::vector<double> &input, double learning_rate)
{

}

std::vector<double> forward_propagation(const std::vector<double>& inputs)
{
    return {};
}