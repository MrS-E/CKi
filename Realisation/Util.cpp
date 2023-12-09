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
