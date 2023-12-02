//
// Created by simeo on 02.12.2023.
//

#include "Util.h"

double Util::sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}
