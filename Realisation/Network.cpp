//
// Created by simeo on 03.12.2023.
//

#include "Network.h"

void Network::add_hidden_layer(int neuron_count) {
    hidden_layers.emplace_back(in_size, neuron_count);
    in_size = neuron_count;
}
void Network::add_input_layer(int neuron_count) {
    input_layer = Layer(neuron_count, neuron_count);
    in_size = neuron_count;
}
void Network::add_output_layer(int neuron_count) {
    output_layer = Layer(in_size, neuron_count);
    out_size = neuron_count;
}

void Network::train(std::vector<std::vector<double>> &inputs, std::vector<std::vector<double>> &labels, int epochs, double learningRate) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        std::cout << "Epoch " << epoch + 1 << " of " << epochs << std::endl;
        for (size_t example = 0; example < inputs.size(); ++example) {
            Network::forward_pass(inputs[example]);

            backpropagation(inputs[example], labels[example], learningRate);
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
    std::vector<double> output = forward_pass(input);
    int digit = 0;
    for (int i = 1; i < out_size; ++i) {
        if (output[i] > output[digit]) {
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

std::vector<double> Network::forward_pass(std::vector<double> &input) {
    std::vector<double> output;
    input_layer.calc_neuron_outputs(input);

    for (auto& hidden_layer : hidden_layers) {
        hidden_layer.calc_neuron_outputs(input_layer.get_neuron_outputs());
        input_layer = hidden_layer;
    }

    output_layer.calc_neuron_outputs(input_layer.get_neuron_outputs());
    for(auto& neuron : output_layer.neurons) {
        output.push_back(neuron.out);
    }
    return output;
}

void Network::backpropagation(std::vector<double> &input, std::vector<double> &label, double learningRate) {
    std::vector<double> output_deltas(out_size);
    for (int i = 0; i < out_size; ++i) {
        output_deltas[i] = output_layer.neurons[i].calc_delta(output_layer.neurons[i].calc_err(label[i]));
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
    output_layer.update_weights(hidden_layers.empty() ? input_layer.get_neuron_outputs() : hidden_layers.front().get_neuron_outputs(), output_deltas, learningRate);
}


// NetworkBuilder
void NetworkBuilder::add_input_layer(int neuron_count) {
    NetworkBuilder::in_size = neuron_count;
}
void NetworkBuilder::add_hidden_layer(int neuron_count) {
NetworkBuilder::hidden_sizes.push_back(neuron_count);
}
void NetworkBuilder::add_output_layer(int neuron_count) {
    NetworkBuilder::out_size = neuron_count;
}
std::vector<int> NetworkBuilder::lookup_sizes() {
    if(NetworkBuilder::in_size==0 || NetworkBuilder::out_size==0 || NetworkBuilder::hidden_sizes.empty()) {
        return {};
    }
    std::vector<int> sizes;
    sizes.push_back(NetworkBuilder::in_size);
    for(int hidden_size : NetworkBuilder::hidden_sizes) {
        sizes.push_back(hidden_size);
    }
    sizes.push_back(NetworkBuilder::out_size);
    return sizes;
}
void NetworkBuilder::printout() {
    std::vector<int> sizes = NetworkBuilder::lookup_sizes();

    if(sizes.empty()) {
        std::cout << "Network Build: " << std::endl;
        std::cout << "No layers added" << std::endl;
        return;
    }
    if(sizes.size()<3){
        std::cout << "Network Build: " << std::endl;
        std::cout << "Not enough layers added" << std::endl;
        return;
    }

    int ins = sizes[0];
    std::cout << "Input layer: (" << ins << "," << ins << ")" << std::endl;
    for(int i=1; i<sizes.size()-1; i++) {
        std::cout << "Hidden layer " << i - 1 << ": (" <<  ins << "," << sizes[i] << ")" << std::endl;
        ins = sizes[i];
    }
    std::cout << "Output layer: (" << ins << "," << sizes[sizes.size()-1] << ")" << std::endl;
}
Network NetworkBuilder::build() {
    std::vector<int> sizes = NetworkBuilder::lookup_sizes();

    if(sizes.empty()) {
        std::cout << "Network Build: " << std::endl;
        std::cout << "No layers added" << std::endl;
        return {};
    }
    if(sizes.size()<3){
        std::cout << "Network Build: " << std::endl;
        std::cout << "Not enough layers added" << std::endl;
        return {};
    }

    Network nn;
    std::cout << in_size << std::endl;
    nn.add_input_layer(in_size);
    for(int hidden_size : hidden_sizes) {
        nn.add_hidden_layer(hidden_size);
    }
    nn.add_output_layer(out_size);
    return nn;
}
