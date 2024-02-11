//
// Created by MrS-E on 11/02/2024.
//

#include "../Layer.h"
#include "gtest/gtest.h"

class LayerTest : public ::testing::Test {
protected:
    std::unique_ptr<Layer> layer;
    const int inputSize = 3;
    const int neuronsCount = 2;

    void SetUp() override {
        layer = std::make_unique<Layer>(inputSize, neuronsCount);
    }
};

TEST_F(LayerTest, LayerInitialization) {
    EXPECT_EQ(layer->neurons.size(), neuronsCount);
    for (auto& neuron : layer->neurons) {
        EXPECT_EQ(neuron.weights.size(), inputSize);
    }
}

TEST_F(LayerTest, SetAndGetWeights) {
    std::vector<double> weights = {0.1, 0.2, 0.3, 0.4};
    layer->neurons[0].weights = weights;
    for (size_t i = 0; i < weights.size(); ++i) {
        EXPECT_DOUBLE_EQ(layer->neurons[0].weights[i], weights[i]);
    }
}

TEST_F(LayerTest, CalculateNeuronOutputs) {
    std::vector<std::vector<double>> weights = {{0.1, 0.2, 0.3},{0.4, 0.5, 0.6}};
    for (size_t i = 0; i < layer->neurons.size(); ++i) {
        layer->neurons[i].weights = weights[i];
    }

    std::vector<double> inputs = {1.0, 2.0};
    layer->calc_neuron_outputs(inputs);
    auto outputs = layer->get_neuron_outputs();

    std::vector<double> expected_outputs = {0.817, 0.916};

    ASSERT_EQ(outputs.size(), expected_outputs.size());
    for (size_t i = 0; i < outputs.size(); ++i) {
        EXPECT_NEAR(outputs[i], expected_outputs[i], 0.001);
    }
}

TEST_F(LayerTest, ErrorCalculation) {
    std::vector<std::vector<double>> weights = {{0.1, 0.2, 0.3},{0.4, 0.5, 0.6}};
    for (size_t i = 0; i < layer->neurons.size(); ++i) {
        layer->neurons[i].weights = weights[i];
    }

    std::vector<double> inputs = {1.0, 2.0};
    layer->calc_neuron_outputs(inputs);
    auto outputs = layer->get_neuron_outputs();

    std::vector<double> error = layer->calculate_error({0.8, 1});
    std::vector<double> expected_error = {0.017, -0.083};

    for (size_t i = 0; i < error.size(); ++i) {
        EXPECT_NEAR(error[i], expected_error[i], 0.001);
    }
}

TEST_F(LayerTest, UpdateWeightsAndBiases) {
    std::vector<std::vector<double>> weights = {{0.1, 0.2, 0.3},{0.4, 0.5, 0.6}};
    for (size_t i = 0; i < layer->neurons.size(); ++i) {
        layer->neurons[i].weights = weights[i];
    }

    std::vector<double> inputs = {1.0, 2.0};
    layer->calc_neuron_outputs(inputs);
    auto outputs = layer->get_neuron_outputs();

    std::vector<double> error = layer->calculate_error({0.8, 1});
    layer->update_weights_and_biases(error, 0.1);

    std::vector<std::vector<double>> expected_weights = {{0.099, 0.199, 0.2999},{0.401, 0.503,  0.5999}};
    std::vector<double> expected_biases = {0.999, 1.001};

    for (size_t i = 0; i < layer->neurons.size(); ++i) {
        EXPECT_NEAR(layer->neurons[i].bias, expected_biases[i], 0.001);
        for (size_t j = 0; j < layer->neurons[i].weights.size(); ++j) {
            EXPECT_NEAR(layer->neurons[i].weights[j], expected_weights[i][j], 0.001);
        }
    }
}

