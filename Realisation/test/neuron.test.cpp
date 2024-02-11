//
// Created by MrS-E on 11/02/2024.
//

#include <gtest/gtest.h>
#include "../Neuron.h"

class NeuronTest : public ::testing::Test {
protected:
    Neuron neuron;

    void SetUp() override {
        neuron.bias = 0.5;
        neuron.weights = {0.1, 0.2};
    }
};

TEST_F(NeuronTest, CalcActivation) {
    std::vector<double> inputs = {1.0, 2.0};
    double expected_activation = neuron.calc_activation(inputs);
    ASSERT_NEAR(expected_activation, 0.731, 0.001);
}

TEST_F(NeuronTest, ActivationDerivative) {
    neuron.calc_activation({1.0, 2.0});
    double expected_derivative = neuron.activation_derivative();
    ASSERT_NEAR(expected_derivative, 0.219, 0.001);
}

TEST_F(NeuronTest, CalcError) {
    neuron.calc_activation({1.0, 2.0});
    double target = 0.8;
    double error = neuron.calc_error(target);
    ASSERT_NEAR(error, neuron.activation - target, 0.001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}