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

void Network::train(std::vector<std::vector<double>> &inputs, std::vector<std::vector<double>> &labels, int epochs, double learning_rate) {
    for(int epoch = 0; epoch<epochs; epoch++ ){
        std::cout << "Epoch: " << epoch + 1 << " of " << epochs << std::endl;
        for(std::size_t i = 0; i < inputs.size(); ++i) {
            std::vector<double> outputs = Network::forward_propagation(inputs[i]);

            Network::backpropagation(labels[i], learning_rate);

        }
    }
}

std::vector<double> Network::forward_propagation(const std::vector<double> &inputs) {
    std::vector<double> outputs = inputs;
    for(auto& layer : Network::layers) {
        outputs = layer.forward_propagation(outputs);
    }
    return outputs;
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
    return static_cast<double>(correct) / inputs.size();
}

void Network::save_weights() {
    for(std::size_t i = 0; i < Network::layers.size(); ++i) {
        std::ofstream file("weights" + std::to_string(i) + ".txt");
        for(auto& neuron : Network::layers[i].neurons) {
            for(auto& weight : neuron.weights) {
                file << weight << " ";
            }
            file << std::endl;
        }
        file.close();
    }

}

void Network::load_weights() {
    for(std::size_t i = 0; i < Network::layers.size(); ++i) {
        std::ifstream file("weights" + std::to_string(i) + ".txt");
        std::vector<std::vector<double>> weights(Network::layers[i].neurons.size());
        for(auto& neuron : weights) {
            neuron.resize(Network::layers[i].neurons[0].weights.size());
        }
        for(std::size_t j = 0; j < Network::layers[i].neurons.size(); ++j) {
            for(std::size_t k = 0; k < Network::layers[i].neurons[j].weights.size(); ++k) {
                file >> weights[j][k];
            }
        }
        Network::layers[i].set_weights(weights);
        file.close();
    }
}


void Network::backpropagation(const std::vector<double> &expected_output, double learning_rate) {
    //implementation after math basics of https://youtu.be/tIeHLnjs5U8?si=rLwae8-ODyXVPCsa
    //todo simplify (split code to functions for layer)

    // Calculate the overall network error (cost)
    double total_error = 0.0;
    Layer output_layer = Network::layers[layers.size() - 1];

    std::vector<double> next_layer_deltas(output_layer.neurons.size());

    for (std::size_t i = 0; i < expected_output.size(); ++i) {
        double error = output_layer.neurons[i].calc_err(expected_output[i]);
        next_layer_deltas[i] = output_layer.neurons[i].calc_delta(error);
        total_error += error;
    }

    // Print or store the cost for monitoring
    std::cout << "Total Error: " << total_error << std::endl;

    // propagate deltas backward through the layers
    // Update weights and biases for the output layer
    for (std::size_t i = 0; i < output_layer.neurons.size(); ++i) {
        for (std::size_t j = 0; j < output_layer.neurons[i].weights.size(); ++j) {
            output_layer.neurons[i].weights[j] +=
                    learning_rate * next_layer_deltas[i] * layers[layers.size() - 2].neurons[j].out;
        }

        output_layer.neurons[i].bias += learning_rate * next_layer_deltas[i];
    }

    // Calculate deltas and update weights and biases for hidden layers
    for (int i = Network::layers.size() - 2; i > 0; --i) {
        Layer current_layer = Network::layers[i];
        Layer next_layer = Network::layers[i + 1];

        std::vector<double> current_layer_deltas(current_layer.neurons.size(), 0.0);

        for (std::size_t j = 0; j < current_layer.neurons.size(); ++j) {
            double sum_weights_deltas = 0.0;

            for (std::size_t k = 0; k < next_layer.neurons.size(); ++k) {
                sum_weights_deltas += next_layer.neurons[k].weights[j] * next_layer_deltas[k];
            }

            current_layer_deltas[j] = current_layer.neurons[j].calc_delta(sum_weights_deltas);

            // Update weights and biases for the current layer
            for (std::size_t k = 0; k < current_layer.neurons[j].weights.size(); ++k) {
                current_layer.neurons[j].weights[k] +=
                        learning_rate * current_layer_deltas[j] * Network::layers[i - 1].neurons[k].out;
            }

            current_layer.neurons[j].bias += learning_rate * current_layer_deltas[j];
        }

        next_layer_deltas = current_layer_deltas;
    }
}


