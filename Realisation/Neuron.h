//
// Created by simeo on 02.12.2023.
//

#ifndef REALISATION_NEURON_H
#define REALISATION_NEURON_H


class Neuron {
public:
    Neuron();
    double calc_out();
    double calc_err();
    double calc_delta();

private:
    double out;
    double bias;
};


#endif //REALISATION_NEURON_H
