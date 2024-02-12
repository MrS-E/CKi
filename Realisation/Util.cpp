//
// Created by simeo on 02.12.2023.
//

#include "Util.h"

double Util::sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double Util::sigmoid_derivative(double x) {
    double s = sigmoid(x);
    return s * (1.0 - s);
}

int Util::read_int(std::ifstream &file) { //https://stackoverflow.com/questions/604431/c-reading-unsigned-char-from-file-stream
    unsigned char bytes[4];
    file.read(reinterpret_cast<char*>(bytes), sizeof(bytes));
    return (int)((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]);
}

//http://yann.lecun.com/exdb/mnist/
std::vector<std::vector<double>> Util::read_mnist_images(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        int magic_number = read_int(file);
        int number_of_images = read_int(file);
        int number_of_rows = read_int(file);
        int number_of_columns = read_int(file);

        std::vector<std::vector<double>> images(number_of_images, std::vector<double>(number_of_rows * number_of_columns));

        for (int i = 0; i < number_of_images; ++i) {
            for (int r = 0; r < number_of_rows * number_of_columns; ++r) {
                unsigned char temp = 0;
                file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
                images[i][r] = (double)temp / 255.0; // Normalizing pixel values to [0, 1]
            }
        }
        return images;
    } else {
        throw std::runtime_error("Cannot open file: " + filename);
    }}

std::vector<double> Util::read_mnist_labels(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        int magic_number = read_int(file);
        int number_of_items = read_int(file);

        std::vector<double> labels(number_of_items);

        for (int i = 0; i < number_of_items; ++i) {
            unsigned char temp = 0;
            file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
            labels[i] = (double)temp;
        }
        return labels;
    } else {
        throw std::runtime_error("Cannot open file: " + filename);
    }
}

int read_int(std::ifstream &file) {
    unsigned char bytes[4];
    file.read(reinterpret_cast<char*>(bytes), sizeof(bytes));
    return (int)((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]);
}

