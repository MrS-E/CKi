#include <iostream>
#include "Network.h"
#include "Util.h"

void train(Network nn){
    std::cout << std::endl << "Training..." << std::endl;
    std::cout << "Reading MNIST data..." << std::endl;
    std::vector<std::vector<double>> training_inputs = Util::read_mnist_training_images("../mnist");
    std::vector<std::vector<double>> training_labels = Util::read_mnist_training_labels("../mnist");

    std::cout << "Training..." << std::endl;
    nn.train(training_inputs, training_labels, 100, 0.1);

    std::cout << "Saving weights..." << std::endl;
    nn.save_weights("weights.txt");
    std::cout << "Done!" << std::endl;
}

double verif(Network nn){
    std::cout << std::endl << "Testing..." << std::endl;

    /*std::cout << "Reading MNIST data..." << std::endl;
    std::vector<std::vector<double>> test_inputs = Util::read_mnist_images("mnist/t10k-images.idx3-ubyte");
    std::vector<std::vector<double>> test_labels = Util::read_mnist_labels("mnist/t10k-labels.idx1-ubyte");

    std::cout << "Testing..." << std::endl;
    double acc = nn.verify(test_inputs, test_labels);
    std::cout << "Accuracy: " << acc << std::endl;*/
    std::cout << "Done!" << std::endl;
    return 0;
}

int main() {
    Network nn (28*28, 10);

    nn.add_hidden_layer(64);
    nn.add_hidden_layer(32);
    
    std::string cmd;
    
    std::cout << "Welcome to CKi" << std::endl;
    do {
        std::cout << "---------------------" << std::endl;
        std::cout << "What do you want do: ";
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
