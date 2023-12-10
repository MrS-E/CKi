//
// Created by MrS-E on 02.12.2023.
//

#ifndef CKI_UTIL_H
#define CKI_UTIL_H

#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class Util {
public:
    static double sigmoid(double x);
    static double sigmoid_derivative(double x);
    static std::vector<std::vector<double>> read_mnist_training_images(const std::string& folder);
    static std::vector<std::vector<double>> read_mnist_training_labels(const std::string& folder);
    static std::vector<std::vector<double>> read_mnist_test_images(const std::string& folder);
    static std::vector<std::vector<double>> read_mnist_test_labels(const std::string& folder);
};


#endif //CKI_UTIL_H
