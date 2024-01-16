//
// Created by MrS-E on 02.12.2023.
//

#include "Neuron.h"

double Neuron::calc_activation(const std::vector<double> &inputs)
{
    double sum = Neuron::bias;
    for (size_t i = 0; i < inputs.size(); ++i) {
        sum += inputs[i] * Neuron::weights[i];
    }
    Neuron::activition = Util::sigmoid(sum);
    Neuron::sum = sum;
    return Neuron::activition;
}

double Neuron::calc_differential_error_divition_differential_activition(double target) const
{
    return Neuron::activition - target;
}

double Neuron::calc_differential_activation_divition_differential_sum() const
{
    return Util::sigmoid_derivative(Neuron::sum);
}