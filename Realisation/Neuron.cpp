//
// Created by MrS-E on 02.12.2023.
//

#include "Neuron.h"

double Neuron::calc_out(const std::vector<double> &inputs) {
    double sum = Neuron::bias;
    for (size_t i = 0; i < inputs.size(); ++i) {
        sum += inputs[i] * Neuron::weights[i];
    }
    Neuron::out = Util::sigmoid(sum);
    return Neuron::out;
}

double Neuron::calc_err(double target) const {
    return target - Neuron::out;
}

double Neuron::calc_delta(double error) const {
    return error * Util::sigmoid_derivative(Neuron::out);
}
