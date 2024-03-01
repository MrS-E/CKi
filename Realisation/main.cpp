//
// Created by simeo on 25/01/2024.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "Network.h"
#include "Util.h"

double train(Network& nn, const std::string &images, const std::string &labels, int epochs = 1, double learning_rate = 0.1){
    std::cout << std::endl << "Training..." << std::endl;
    std::cout << "Reading MNIST data..." << std::endl;
    std::vector<std::vector<double>> training_inputs = Util::read_mnist_images(images);
    std::vector<double> training_labels = Util::read_mnist_labels(labels);

    std::cout << "Training..." << std::endl;
    double error = nn.train(training_inputs, training_labels, epochs, learning_rate);
    std::cout << "Error: " << error << std::endl;

    std::cout << "Done!" << std::endl;
    return error;
}
double verif(Network& nn, const std::string &images, const std::string &labels){
    std::cout << std::endl << "Testing..." << std::endl;
    std::cout << "Reading MNIST data..." << std::endl;
    std::vector<std::vector<double>> test_inputs = Util::read_mnist_images(images);
    std::vector<double> test_labels = Util::read_mnist_labels(labels);

    std::cout << "Testing..." << std::endl;
    double acc = nn.verify(test_inputs, test_labels);
    std::cout << "Accuracy: " << acc*100 << "%" << std::endl;
    std::cout << "Done!" << std::endl;
    return acc;
}

std::vector<double> process_image(const char* filename) {
    int width, height, channels;
    unsigned char* img = stbi_load(filename, &width, &height, &channels, 0);
    if (img == nullptr) {
        std::cerr << "Error in loading the image" << std::endl;
        exit(1);
    }

    unsigned char* resized_img = new unsigned char[28 * 28 * channels];
    stbir_resize_uint8(img, width, height, 0, resized_img, 28, 28, 0, channels);

    std::vector<double> image_data(28 * 28);
    for (int i = 0; i < 28 * 28; ++i) {
        int j = i * channels;
        double gray = 0.299 * resized_img[j] + 0.587 * resized_img[j + 1] + 0.114 * resized_img[j + 2];
        image_data[i] = gray / 255.0; // Normalize to [0, 1]
    }

    stbi_image_free(img);
    delete[] resized_img;

    return image_data;
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

    std::vector <std::string> tokens;
};

int main(int argc, char * argv[]) {
    Network nn(784, 10, {32, 16});
    InputParser input(argc, argv);
    std::string filename = input.tokens[input.tokens.size()-1];

    if(input.cmdOptionExists("--help"))
    {
        std::cout << "CKi Application Help\n\n"
         << "Usage:\n"
         << "  ki --help\t\tShow this help message.\n"
         << "  ki --train -l [label] -i [images] < -e [epoch] > < -lr [learningrate] >\tTrain the CNN with a dataset in ubyte format.\n"
         << "  ki --verify -l [label] -i [images]\tVerify the trained model accuracy with a dataset in ubyte format.\n"
         << "  ki [file]\t\tPredict the digit in a jpg image file.\n\n"
         << "Options:\n"
         << "  --help\t\tShow help information.\n"
         << "  --training\t\tInitiate model training with specified dataset.\n"
         << "  --verify\t\tVerify model with specified dataset.\n"
         << "  [file]\t\tThe path to the input file for training, verification, or prediction.\n\n"
         << "Example:\n"
         << "  ki --train -i data/train-images-idx3-ubyte -l data/train-labels-idx3-ubyte\n"
         << "  ki --verify -i data/t10k-images-idx3-ubyte -l data/t10k-labels-idx3-ubyte\n"
         << "  ki image.jpg\n\n"
         << "For more information, visit github.com/MrS-E/CKi.\n" << std::endl;
    }
    else
    {
        try{
            std::cout << "Loading network..." << std::endl;
            nn.load_network("network.json");
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        try{
            if (input.tokens.size() > 0)
            {
                if(input.cmdOptionExists("--verify"))
                {
                    //verify
                    if(input.cmdOptionExists("-l") && input.cmdOptionExists("-i"))
                    {
                        std::string images = input.getCmdOption("-i");
                        std::string labels = input.getCmdOption("-l");
                        verif(nn, images, labels);
                    }
                    else
                    {
                        std::cout << "Dataset needed, type --help for more information." << std::endl;
                    };
                }
                else if(input.cmdOptionExists("--train"))
                {
                    //train
                    if(input.cmdOptionExists("-l") && input.cmdOptionExists("-i"))
                    {
                        std::string images = input.getCmdOption("-i");
                        std::string labels = input.getCmdOption("-l");
                        int epochs = input.cmdOptionExists("-e") ? std::stoi(input.getCmdOption("-e")) : 1;
                        double learning_rate = input.cmdOptionExists("-lr") ? std::stod(input.getCmdOption("-lr")) : 0.1;
                        train(nn, images, labels, epochs, learning_rate);
                        std::cout << "Saving network..." << std::endl;
                        nn.save_network("network.json");
                    }
                    else
                    {
                        std::cout << "Dataset needed, type --help for more information." << std::endl;
                    };
                }
                else
                {
                    if(std::filesystem::exists(filename)){
                        //predic
                        std::vector<double> image = process_image(filename.c_str());
                        std::vector<double> outputs = nn.predict(image);
                        int result = static_cast<int>(std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end())));
                        for (size_t i=0; i<outputs.size(); i++)
                        {
                            std::cout << "Ziffer " << i <<": " << outputs[i]*100 << "%" << std::endl;
                        }
                        std::cout << "------------------------" << std::endl;
                        std::cout << "Predicted digit: " << result << std::endl;
                    }else{
                        std::cout << "File needed, type --help for more information." << std::endl;
                    }
                }
            }
            else
            {
                std::cout << "Unknown Error" << std::endl;
            }
        }catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}
