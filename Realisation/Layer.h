//
// Created by simeo on 02.12.2023.
//

#ifndef REALISATION_LAYER_H
#define REALISATION_LAYER_H

#include<vector>
#include"Neuron.h"

class Layer {

private:
    std::vector<Neuron> neurons;
    std::vector<std::vector<double>> weights;
};


#endif //REALISATION_LAYER_H
