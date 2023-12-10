//
// Created by MrS-E on 03.12.2023.
//

#include "Network.h"

Network::Network(int in_size, int out_size, std::vector<int> hidden_layers_sizes) {
    for(auto& layer_size : hidden_layers_sizes) {
        Network::layers.emplace_back(in_size, layer_size);
        in_size = layer_size;
    }
    Network::layers.emplace_back(in_size, out_size);
}

void Network::train(std::vector<std::vector<double>> &inputs, std::vector<std::vector<double>> &labels, int epochs, double learning_rate) {
    for(int epoch = 0; epoch<epochs; epoch++ ){
        for(std::size_t i = 0; i < inputs.size(); ++i) {
            std::vector<double> outputs = Network::forward_propagation(inputs[i]);

            std::vector<double> deltas_out = Network::layers.back().get_deltas(labels[i]);

            for(int j = Network::layers.size() - 2; j >= 0; --j) {
                deltas_out = Network::layers[j].backward_propagation(Network::layers[j+1].get_neuron_outputs(), deltas_out, learning_rate);
            }

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



