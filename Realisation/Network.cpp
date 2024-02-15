//
// Created by MrS-E on 03.12.2023.
//

#include "Network.h"

Network::Network(int in_size, int out_size, std::vector<int> hidden_layers_sizes) {
    Network::layers.emplace_back(in_size, in_size);
    for(auto& layer_size : hidden_layers_sizes) {
        Network::layers.emplace_back(in_size, layer_size);
        in_size = layer_size;
    }
    Network::layers.emplace_back(in_size, out_size);
}

int Network::predict(const std::vector<double> &input) {
    std::vector<double> outputs = Network::forward_propagation(input);
    return static_cast<int>(std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end()))); //return number of the neuron with the highest output +1
}

double Network::verify(const std::vector<std::vector<double>> &inputs, const std::vector<double> &labels) {
    int correct = 0;
    for (std::size_t i = 0; i < inputs.size(); ++i) {
        if (Network::predict(std::vector<double>(inputs[i])) == static_cast<int>(labels[i])) {
            correct++;
        }
    }
    return static_cast<double>(correct) / static_cast<double>(inputs.size());
}

double Network::train(std::vector<std::vector<double>> &inputs, std::vector<double> &labels, int epochs, double learning_rate) {
    double total_error = 0;
    for(int epoch = 0; epoch<epochs; epoch++ ){
        for(std::size_t i = 0; i < inputs.size(); i++) {
            std::vector<double> outputs = Network::forward_propagation(inputs[i]);
            total_error += Network::backward_propagation(labels[i], learning_rate);
            total_error /= 2;
        }
    }
    return total_error;
}

 std::vector<double> Network::forward_propagation(const std::vector<double>& input) {
    layers[0].calc_neuron_outputs(input);

    for (int i = 1; i < layers.size(); ++i) {
        std::vector<double> inputs = layers[i - 1].get_neuron_outputs();
        layers[i].calc_neuron_outputs(inputs);
    }

    return layers[layers.size()-1].get_neuron_outputs();
}

double Network::backward_propagation(const int& target, double learning_rate) {
    std::vector<double> inputs (10, 0);
    inputs[target] = 1;
    std::vector<double> error = layers[layers.size()-1].calculate_error(inputs);
    double total_error = 0;
    for(double& e : error) {
        total_error += e;
    }

    total_error/=error.size();

    //std::cout << total_error << std::endl;

    for (int i = layers.size() - 1; i >= 0; --i) {
        error = layers[i].update_weights_and_biases(error, learning_rate);
    }
    return total_error;
}

void Network::save_network(const std::string &filename) {
    nlohmann::json j;

    for (size_t i = 0; i < layers.size(); ++i) {
        for (const auto& neuron : layers[i].neurons) {
            j["layers"][i]["neurons"].push_back({
                                                        {"weights", neuron.weights},
                                                        {"bias", neuron.bias}
                                                });
        }
    }

    std::ofstream file(filename);
    file << j.dump(4);
}

void Network::load_network(const std::string &filename) {
    std::ifstream file(filename);
    nlohmann::json j;
    file >> j;

    for (size_t i = 0; i < layers.size(); ++i) {
        size_t neuronIndex = 0;
        for (auto& neuron : layers[i].neurons) {
            neuron.weights = j["layers"][i]["neurons"][neuronIndex]["weights"].get<std::vector<double>>();
            neuron.bias = j["layers"][i]["neurons"][neuronIndex]["bias"].get<double>();
            neuronIndex++;
        }
    }
}
