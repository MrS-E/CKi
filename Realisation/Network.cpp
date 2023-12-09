//
// Created by simeo on 03.12.2023.
//

#include "Network.h"

Network::Network(int in_size, int out_size) : input_layer(in_size, in_size), output_layer(in_size, out_size), in_size(in_size), out_size(out_size) {
    /*load_weights("weights_input.txt", input_layer.weights); todo: fix after moving weights to Neuron
    for (size_t i = 0; i < hidden_layers.size(); ++i) {
        load_weights("weights_hidden_" + std::to_string(i) + ".txt", hidden_layers[i].weights);
    }
    load_weights("weights_output.txt", output_layer.weights);*/
}

void Network::add_hidden_layer(int neuron_count) {
    hidden_layers.emplace_back(in_size, neuron_count);
    in_size = neuron_count;
}

void Network::train(std::vector<std::vector<double>> &inputs, std::vector<std::vector<double>> &labels, int epochs, double learningRate) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        std::cout << "Epoch " << epoch + 1 << " of " << epochs << std::endl;
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
                std::vector<double> hidden_deltas(it->neurons.size());
                for (size_t i = 0; i < it->neurons.size(); ++i) {
                    double error = 0.0;
                    for (size_t j = 0; j < out_size; ++j) {
                        error += output_deltas[j] * output_layer.neurons[i].weights[j];
                    }
                    hidden_deltas[i] = it->neurons[i].calc_delta(error);
                }

                // Update weights
                it->update_weights((it + 1)->get_neuron_outputs(), hidden_deltas, learningRate);
            }

            // Update output layer weights
            output_layer.update_weights(hidden_layers.empty() ? input_layer.get_neuron_outputs() : hidden_layers.front().get_neuron_outputs(), output_deltas, learningRate);
        }
    }
}

double Network::verify(const std::vector<std::vector<double>> &inputs, const std::vector<std::vector<double>> &labels) {
    if (inputs.size() != labels.size() || inputs.empty()) {
        std::cerr << "Invalid test data." << std::endl;
        return 0.0;
    }

    int corr_predictions = 0;

    for (size_t i = 0; i < inputs.size(); ++i) {
        std::cout << "Predicting digit " << i+1 << " of " << inputs.size() << std::endl;
        int predictedDigit = predict(const_cast<std::vector<double> &>(inputs[i]));

        int trueDigit = static_cast<int>(std::distance(labels[i].begin(), std::max_element(labels[i].begin(), labels[i].end())));
        if (predictedDigit == trueDigit) {
            corr_predictions++;
        }
    }

    double accuracy = static_cast<double>(corr_predictions) / static_cast<double>(inputs.size());
    std::cout << "Verification Accuracy: " << (accuracy * 100.0) << "%" << std::endl;

    return accuracy;
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
    /*std::ofstream out_file(filename); todo:fix after moving weights to Neuron
    if (!out_file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (auto & weight : input_layer.weights) {
        for (double j : weight) {
            out_file << j << " ";
        }
        out_file << std::endl;
    }
    
    for (const auto& hidden_layer : hidden_layers) {
        for (const auto & weight : hidden_layer.weights) {
            for (double j : weight) {
                out_file << j << " ";
            }
            out_file << std::endl;
        }
    }

    for (auto & weight : output_layer.weights) {
        for (double j : weight) {
            out_file << j << " ";
        }
        out_file << std::endl;
    }

    out_file.close();*/
}

void Network::load_weights(const std::string &filename, std::vector<std::vector<double>>& weights) {
    std::ifstream in_file(filename);
    if (!in_file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (auto & weight : weights) {
        for (double & j : weight) {
            in_file >> j;
        }
    }

    in_file.close();
}
