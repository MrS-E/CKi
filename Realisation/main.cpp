#include <iostream>
#include "Network.h"
#include "Util.h"

void train(Network nn){
    std::string filename;
    std::cout << std::endl << "Training..." << std::endl;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    std::vector<std::vector<double>> training_inputs = Util::read_mnist_images(filename);
    std::vector<std::vector<double>> training_labels = Util::read_mnist_labels(filename);

    nn.train(training_inputs, training_labels, 100, 0.1);

    nn.save_weights("weights.txt");
}

double verif(Network nn){
    std::string filename;
    std::cout << std::endl << "Testing..." << std::endl;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    std::vector<std::vector<double>> test_inputs = Util::read_mnist_images(filename);
    std::vector<std::vector<double>> test_labels = Util::read_mnist_labels(filename);

    double acc = nn.verify(test_inputs, test_labels);
    return acc;
}

int main() {
    Network nn (28*28, 10);

    nn.add_hidden_layer(64);
    nn.add_hidden_layer(32);
    
    std::string cmd;
    
    std::cout << "Welcome to CKi" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "What do you want do: ";
    do {
        std::cin >> cmd;

        if (cmd == "train") {
            train(nn);
        } else if (cmd == "test") {
            verif(nn);
        } else if (cmd == "exit") {
            std::cout << "Exiting..." << std::endl;
            break;
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }while(!cmd.empty());

    return 0;
}
