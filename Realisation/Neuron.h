//
// Created by MrS-E on 02.12.2023.
//

#ifndef REALISATION_NEURON_H
#define REALISATION_NEURON_H

#include <vector>
#include "Util.h"

class Neuron {
public:
    Neuron() {};
    double calc_out(const std::vector<double>& inputs);
    double calc_err(double target);
    double calc_delta(double error);
    double out;
    std::vector<double> weights;

private:
    double bias = 1.0;
};


#endif //REALISATION_NEURON_H
