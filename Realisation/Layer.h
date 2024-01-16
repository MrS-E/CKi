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
    void set_weights(const std::vector<std::vector<double>>& weights);
    std::vector<double> forward_propagation(const std::vector<double>& inputs);
    void backward_propagation(const std::vector<double>& inputs);

    std::vector<Neuron> neurons;
};


#endif //REALISATION_LAYER_H
