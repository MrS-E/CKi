//
// Created by MrS-E on 02.12.2023.
//

#ifndef REALISATION_LAYER_H
#define REALISATION_LAYER_H

#include<vector>
#include <cstdlib>
#include <ctime>
#include"Neuron.h"

class Layer {
public:
    Layer(int inputSize, int neuron_count);
    void calc_neuron_outputs(const std::vector<double>& inputs);
    std::vector<double> get_neuron_outputs();
    void init_weights();
    std::vector<double> update_weights_and_biases(const std::vector<double>& error, double learning_rate);
    std::vector<double> calculate_error(const std::vector<double>& target);

    std::vector<Neuron> neurons;
};


#endif //REALISATION_LAYER_H
