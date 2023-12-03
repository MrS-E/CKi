//
// Created by MrS-E on 02.12.2023.
//

#include "Neuron.h"

double Neuron::calc_out(const std::vector<double> &inputs, const std::vector<double> &weights) {
    double sum = Neuron::bias;
    for (size_t i = 0; i < inputs.size(); ++i) {
        sum += inputs[i] * weights[i];
    }
    Neuron::out = Util::sigmoid(sum);
    return Neuron::out;
}

double Neuron::calc_err(double target) {
    return target - Neuron::out;
}

double Neuron::calc_delta(double error) {
    return error * Util::sigmoid_derivative(Neuron::out);
}
