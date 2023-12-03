#include <iostream>
#include "Network.h"

int main() {
    Network nn (28*28, 10);

    nn.add_hidden_layer(64);
    nn.add_hidden_layer(32);

    std::vector<std::vector<double>> training_inputs = {{/* input data */}};
    std::vector<std::vector<double>> training_labels = {{/* corresponding labels */}};

    nn.train(training_inputs, training_labels, 100, 0.1);

    std::vector<std::vector<double>> test_inputs = {{/* test input data */}};
    std::vector<std::vector<double>> test_labels = {{/* corresponding labels */}};

    nn.verify(test_inputs, test_labels);

    nn.save_weights("weights.txt");

    return 0;
}
