//
// Created by simeo on 02.12.2023.
//

#include <cstdint>
#include "Util.h"
#include "mnist/mnist_reader.hpp"

double Util::sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double Util::sigmoid_derivative(double x) {
    double s = sigmoid(x);
    return s * (1.0 - s);
}

double Util::relu(double x)
{
    return std::max(0.0, x);
}

double Util::relu_derivative(double x)
{
    return (x > 0) * 1;
}

std::vector<std::vector<double>> Util::read_mnist_training_images(const std::string &folder) {
    auto dataset = mnist::read_dataset<std::vector, std::vector, double, uint8_t>(folder);

    std::vector<std::vector<double>> images;
    images.reserve(dataset.training_images.size());
    for ( auto image : dataset.training_images) {
        for(double & p : image) {
            p = p / 255.0;
        }
        images.push_back(image);
    }

    return images;
}

std::vector<std::vector<double>> Util::read_mnist_training_labels(const std::string &folder) {
    auto dataset = mnist::read_dataset<std::vector, std::vector, double, uint8_t>(folder);

    std::vector<std::vector<double>> labels;
    labels.reserve(dataset.training_labels.size());
    for (const auto& label : dataset.training_labels) {
        std::vector<double> label_vec(10, 0.0);
        label_vec[label] = 1.0;
        labels.push_back(label_vec);
    }

    return labels;
}

std::vector<std::vector<double>> Util::read_mnist_test_images(const std::string &folder) { //todo simplify (combine with read_mnist_training_images)
    auto dataset = mnist::read_dataset<std::vector, std::vector, double, uint8_t>(folder);

    std::vector<std::vector<double>> images;
    images.reserve(dataset.test_images.size());
    for ( auto image : dataset.test_images) {
        for(double & p : image) {
            p = p / 255.0;
        }
        images.push_back(image);
    }

    return images;
}

std::vector<std::vector<double>> Util::read_mnist_test_labels(const std::string &folder) { //todo simplify (combine with read_mnist_training_labels)
    auto dataset = mnist::read_dataset<std::vector, std::vector, double, uint8_t>(folder);

    std::vector<std::vector<double>> labels;
    labels.reserve(dataset.test_labels.size());
    for (const auto& label : dataset.test_labels) {
        std::vector<double> label_vec(10, 0.0);
        label_vec[label] = 1.0;
        labels.push_back(label_vec);
    }

    return labels;
}
