//
// Created by simeo on 02.12.2023.
//

#ifndef REALISATION_LAYER_H
#define REALISATION_LAYER_H

#include<vector>
#include"Neuron.h"

class Layer {
public:
    Layer(int inputSize, int neuronCount);
    void calc_neuron_outputs(const std::vector<double>& inputs);
    std::vector<double> get_neuron_outputs();
    void update_weights(const std::vector<double>& inputs, std::vector<double>& deltas, double learningRate);
    void init_weights();

    std::vector<std::vector<double>> weights;
    std::vector<Neuron> neurons;
};


#endif //REALISATION_LAYER_H
