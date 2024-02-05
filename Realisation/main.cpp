//
// Created by simeo on 25/01/2024.
//
#include <iostream>
#include "Network.h"
#include "Util.h"

void train(Network& nn){
    std::cout << std::endl << "Training..." << std::endl;
    std::cout << "Reading MNIST data..." << std::endl;
    std::vector<std::vector<double>> training_inputs = Util::read_mnist_training_images("../mnist");
    std::vector<std::vector<double>> training_labels = Util::read_mnist_training_labels("../mnist");

    std::cout << "Training..." << std::endl;
    double error = nn.train(training_inputs, training_labels, 100, 0.1);
    std::cout << "Error " << error << std::endl;

    std::cout << "Done!" << std::endl;
}

double verif(Network& nn){
    std::cout << std::endl << "Testing..." << std::endl;
    std::cout << "Reading MNIST data..." << std::endl;
    std::vector<std::vector<double>> test_inputs = Util::read_mnist_test_images("../mnist");
    std::vector<std::vector<double>> test_labels = Util::read_mnist_test_labels("../mnist");

    std::cout << "Testing..." << std::endl;
    double acc = nn.verify(test_inputs, test_labels);
    std::cout << "Accuracy: " << acc << std::endl;
    std::cout << "Done!" << std::endl;
    return acc;
}

int main() {
    Network nn(784, 10, {32, 16});
    train(nn);
    verif(nn);
    return 0;
}
