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

std::vector<double> Layer::calculate_error(const std::vector<double>& target) {
    std::vector<double> layer_error;
   for(std::size_t n = 0; n < Layer::neurons.size(); n++)
   {
       layer_error.push_back(Layer::neurons[n].calc_error(target[n]));
   }
    return layer_error;
}

std::vector<double> Layer::update_weights_and_biases(const std::vector<double>& error, double learning_rate) {
    std::vector<double> prev_layer_error(Layer::neurons[0].weights.size(), 0.0);

    for (size_t i = 0; i < Layer::neurons.size(); ++i) {
        Neuron &neuron = Layer::neurons[i];
        const double neuron_error = error[i];
        const double activation_derivative = neuron.activation_derivative();

        for (size_t j = 0; j < neuron.weights.size(); ++j) {
            prev_layer_error[j] += neuron.weights[j] * neuron_error;

            const double delta_weight = neuron_error * activation_derivative * neuron.inputs[j];
            neuron.weights[j] -= learning_rate * delta_weight;
        }
        neuron.bias -= learning_rate * neuron_error * activation_derivative; //FIXME is it + or -? test with + =  42.31% and - = 61.85%
    }

    return prev_layer_error;
}
