#include <iostream>
#include "Network.h"
#include "Util.h"

void train(Network& nn){
    std::cout << std::endl << "Training..." << std::endl;
    std::cout << "Reading MNIST data..." << std::endl;
    std::vector<std::vector<double>> training_inputs = Util::read_mnist_training_images("../mnist");
    std::vector<std::vector<double>> training_labels = Util::read_mnist_training_labels("../mnist");

    std::cout << "Training..." << std::endl;
    nn.train(training_inputs, training_labels, 1, 0.01);

    std::cout << "Saving weights..." << std::endl;
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
    //nn.load_weights();
    train(nn);
    verif(nn);
    /*std::string cmd;

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
            nn.save_weights();
            break;
        } else {
            std::cout << "Unknown command" << std::endl;
        }
    }while(!cmd.empty());*/

    return 0;
}
