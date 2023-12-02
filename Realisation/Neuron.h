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
    double calc_out(std::vector<double>& inputs, std::vector<double>& weights);
    double calc_err(double target);
    double calc_delta();

private:
    double out;
    double bias = 1.0;
};


#endif //REALISATION_NEURON_H
