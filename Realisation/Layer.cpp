//
// Created by simeo on 02.12.2023.
//

#include "Layer.h"

Layer::Layer(int inputSize, int neuronCount) {
    neurons.resize(neuronCount);
    weights.resize(neuronCount, std::vector<double>(inputSize));
}
