//
// Created by simeo on 03.12.2023.
//

#include "Network.h"

Network::Network(int in_size, int out_size) : input_layer(in_size, in_size), output_layer(in_size, out_size), in_size(in_size), out_size(out_size) {
    load_weights("weights_input.txt", input_layer.weights);
    for (size_t i = 0; i < hidden_layers.size(); ++i) {
        load_weights("weights_hidden_" + std::to_string(i) + ".txt", hidden_layers[i].weights);
    }
    load_weights("weights_output.txt", output_layer.weights);
}

void Network::add_hidden_layer(int neuron_count) {
    hidden_layers.emplace_back(in_size, neuron_count);
    in_size = neuron_count;
}

void Network::train(std::vector<std::vector<double>> &inputs, std::vector<std::vector<double>> &labels, int epochs, double learningRate) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t example = 0; example < inputs.size(); ++example) {
            // Forward pass
            input_layer.calc_neuron_outputs(inputs[example]);

            for (auto& hidden_layer : hidden_layers) {
                hidden_layer.calc_neuron_outputs(input_layer.get_neuron_outputs());
                input_layer = hidden_layer;
            }

            output_layer.calc_neuron_outputs(input_layer.get_neuron_outputs());

            // Backpropagation
            std::vector<double> output_deltas(out_size);
            for (int i = 0; i < out_size; ++i) {
                output_deltas[i] = output_layer.neurons[i].calc_delta(output_layer.neurons[i].calc_err(labels[example][i]));
            }

            for (auto it = hidden_layers.rbegin(); it != hidden_layers.rend(); ++it) {
                std::vector<double> hiddenDeltas(it->neurons.size());
                for (size_t i = 0; i < it->neurons.size(); ++i) {
                    double error = 0.0;
                    for (size_t j = 0; j < out_size; ++j) {
                        error += output_deltas[j] * output_layer.weights[j][i];
                    }
                    hiddenDeltas[i] = it->neurons[i].calc_delta(error);
                }

                // Update weights
                it->update_weights((it + 1)->get_neuron_outputs(), hiddenDeltas, learningRate);
            }

            // Update output layer weights
            output_layer.update_weights(hidden_layers.empty() ? input_layer.get_neuron_outputs() : hidden_layers.front().get_neuron_outputs(), output_deltas, learningRate);
        }
    }
}

double Network::verify(const std::vector<std::vector<double>> &inputs, const std::vector<std::vector<double>> &labels) {
    return 0;
}

int Network::predict(std::vector<double> &input) {
    input_layer.calc_neuron_outputs(input);

    for (auto& hidden_layer : hidden_layers) {
        hidden_layer.calc_neuron_outputs(input_layer.get_neuron_outputs());
        input_layer = hidden_layer;
    }

    output_layer.calc_neuron_outputs(input_layer.get_neuron_outputs());

    int digit = 0;
    for (int i = 1; i < out_size; ++i) {
        if (output_layer.neurons[i].out > output_layer.neurons[digit].out) {
            digit = i;
        }
    }

    return digit;
}

void Network::save_weights(const std::string &filename) {

}

void Network::load_weights(const std::string &filename, std::vector<std::vector<double>>& weights) {

}
