//
// Created by simeo on 25/01/2024.
//
#include <iostream>
#include <algorithm>
#include "Network.h"
#include "Util.h"

void train(Network& nn, const std::string &filename){
    std::cout << std::endl << "Training..." << std::endl;
    std::cout << "Reading MNIST data..." << std::endl;
    std::vector<std::vector<double>> training_inputs = Util::read_mnist_images(filename);
    std::vector<double> training_labels = Util::read_mnist_labels(filename);

   std::cout << "Training..." << std::endl;
    double error = nn.train(training_inputs, training_labels, 1, 0.1);
    std::cout << "Error " << error << std::endl;

    std::cout << "Done!" << std::endl;
}
double verif(Network& nn, const std::string &filename){
    std::cout << std::endl << "Testing..." << std::endl;
    std::cout << "Reading MNIST data..." << std::endl;
    std::vector<std::vector<double>> test_inputs = Util::read_mnist_images(filename);
    std::vector<double> test_labels = Util::read_mnist_labels(filename);

    std::cout << "Testing..." << std::endl;
    double acc = nn.verify(test_inputs, test_labels);
    std::cout << "Accuracy: " << acc << std::endl;
    std::cout << "Done!" << std::endl;
    return acc;
}

class InputParser{ //from: https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
public:
    InputParser (int &argc, char **argv){
        for (int i=1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }
    /// @author iain
    const std::string& getCmdOption(const std::string &option) const{
        std::vector<std::string>::const_iterator itr;
        itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()){
            return *itr;
        }
        static const std::string empty_string("");
        return empty_string;
    }
    /// @author iain
    bool cmdOptionExists(const std::string &option) const{
        return std::find(this->tokens.begin(), this->tokens.end(), option)
               != this->tokens.end();
    }
private:
    std::vector <std::string> tokens;
};

int main(int argc, char * argv[]) {
    Network nn(784, 10, {32, 16});
    InputParser input(argc, argv);
    const std::string &filename = input.getCmdOption("-f");

    try {
        if(input.cmdOptionExists("-h"))
        {
            std::cout << "CKi Application Help\n\n"
             << "Usage:\n"
             << "  ki -h\t\tShow this help message.\n"
             << "  ki -t [file]\tTrain the CNN with a dataset in ubyte format.\n"
             << "  ki -v [file]\tVerify the trained model accuracy with a dataset in ubyte format.\n"
             << "  ki [file]\t\tPredict the digit in a jpg image file.\n\n"
             << "Options:\n"
             << "  --help\t\tShow help information.\n"
             << "  --training\t\tInitiate model training with specified dataset.\n"
             << "  --verify\t\tVerify model with specified dataset.\n"
             << "  [file]\t\tThe path to the input file for training, verification, or prediction.\n\n"
             << "Example:\n"
             << "  ki --training data/train-images-idx3-ubyte\n"
             << "  ki --verify data/t10k-images-idx3-ubyte\n"
             << "  ki image.jpg\n\n"
             << "For more information, visit github.com/MrS-E/CKi.\n" << std::endl;
        }
        else
        {
            if (!filename.empty()){
                if(input.cmdOptionExists("-v"))
                {
                    verif(nn, filename);
                }
                else if(input.cmdOptionExists("-t"))
                {
                    train(nn, filename);
                }
                else
                {
                    //predict
                }
            }
            else
            {
                //file needed
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}