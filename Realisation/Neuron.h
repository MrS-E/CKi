//
// Created by MrS-E on 02.12.2023.
//

#ifndef REALISATION_NEURON_H
#define REALISATION_NEURON_H

#include <vector>
#include "Util.h"

class Neuron {
public:
    Neuron() = default;
    double calc_activation(const std::vector<double>& inputs);
    [[nodiscard]] double calc_differential_error_divition_differential_activition(double target) const;
    [[nodiscard]] double calc_differential_activation_divition_differential_sum() const;

    std::vector<double> weights;
    double activation{};
    double bias = 1.0;
    double sum{};
};

#endif //REALISATION_NEURON_H
