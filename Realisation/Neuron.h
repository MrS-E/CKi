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
    [[nodiscard]] double activation_derivative() const;
    [[nodiscard]] double calc_error(const double &target) const;

    std::vector<double> weights;
    std::vector<double> inputs;
    double activation{};
    double bias = 1.0;
};

#endif //REALISATION_NEURON_H
