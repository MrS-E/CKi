//
// Created by simeo on 02.12.2023.
//

#include <cstdint>
#include "Util.h"

double Util::sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double Util::sigmoid_derivative(double x) {
    double s = sigmoid(x);
    return s * (1.0 - s);
}

std::vector<std::vector<double>> Util::read_mnist_images(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return {};
    }

    uint32_t magic_number, num_images, num_rows, num_cols;
    file.read(reinterpret_cast<char*>(&magic_number), sizeof(magic_number));
    file.read(reinterpret_cast<char*>(&num_images), sizeof(num_images));
    file.read(reinterpret_cast<char*>(&num_rows), sizeof(num_rows));
    file.read(reinterpret_cast<char*>(&num_cols), sizeof(num_cols));

    if (magic_number != 0x03080000) { //number from documentation (indirectly)
        std::cerr << "Invalid magic number for MNIST image file: " << magic_number << std::endl;
        return {};
    }

    std::vector<std::vector<double>> images(num_images, std::vector<double>(num_rows * num_cols));
    for (size_t i = 0; i < num_images; ++i) {
        for (size_t j = 0; j < num_rows * num_cols; ++j) {
            uint8_t pixelValue;
            file.read(reinterpret_cast<char*>(&pixelValue), sizeof(pixelValue));
            images[i][j] = static_cast<double>(pixelValue) / 255.0;  // Normalize pixel values to the range [0, 1]
        }
    }

    file.close();
    return images;
}