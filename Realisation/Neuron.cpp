//
// Created by MrS-E on 02.12.2023.
//

#include "Neuron.h"

double Neuron::calc_activation(const std::vector<double> &inputs)
{
    double sum = Neuron::bias;
    Neuron::inputs = inputs;
    for (size_t i = 0; i < inputs.size(); ++i) {
        sum += inputs[i] * Neuron::weights[i];
    }
    Neuron::activation = Util::sigmoid(sum);
    return Neuron::activation;
}

double Neuron::activation_derivative() const
{
    return Util::sigmoid_derivative(Neuron::activation);
}

double Neuron::calc_error(const double &target) const
{
    return Neuron::activation - target;
}