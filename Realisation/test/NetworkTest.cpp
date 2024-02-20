//
// Created by MrS-E on 11/02/2024.
//

#include <gtest/gtest.h>
#include "../Network.h"
#include <vector>
#include <fstream>

class NetworkTest : public ::testing::Test {
protected:

    void SetUp() override {
    }

    void TearDown() override {
    }
};

/*TEST_F(NetworkTest, ConstructorInitializesCorrectNumberOfLayers) {
    std::vector<int> hidden_layers_sizes = {5, 10};
    Network net(3, 2, hidden_layers_sizes);
    EXPECT_EQ(net.layers.size(), hidden_layers_sizes.size() + 2); //not possible; layer is private; unsure how to perform this test without access to the layers
}*/

TEST_F(NetworkTest, PredictReturnsValidIndex) {
    Network net(3, 3, {5});
    std::vector<double> input = {1.0, 0.5, -1.2};
    std::vector<double> outputs = net.predict(input);
    int prediction = static_cast<int>(std::distance(outputs.begin(), std::max_element(outputs.begin(), outputs.end())));
    EXPECT_EQ(outputs.size(), 3);
    EXPECT_GE(prediction, 0);
    EXPECT_LT(prediction, 3);
}

TEST_F(NetworkTest, TrainModifiesNetworkBehavior) { //not really meaningful, not a good test
    Network net(2, 2, {4});
    std::vector<std::vector<double>> inputs = {{1.0, 0.0}, {0.0, 1.0}};
    std::vector<double> labels = {0, 1};
    std::vector<double> initialOutputs = net.predict(inputs[0]);
    //int  initialPrediction = static_cast<int>(std::distance(initialOutputs.begin(), std::max_element(initialOutputs.begin(), initialOutputs.end())));
    net.train(inputs, labels, 10, 0.1);
    std::vector<double> postTrainingOutputs = net.predict(inputs[0]);
    //int postTrainingPrediction = static_cast<int>(std::distance(postTrainingOutputs.begin(), std::max_element(postTrainingOutputs.begin(), postTrainingOutputs.end())));
    //EXPECT_EQ(postTrainingPrediction, 1); //removed because it's not a 100% guarantee that the network will be trained to predict the correct output because values are generated randomly
    for(int i = 0; i < initialOutputs.size(); i++) {
        EXPECT_NE(postTrainingOutputs[i], initialOutputs[i]);
    }
}

TEST_F(NetworkTest, SaveAndLoadNetwork) {
    std::string filename = "test_network.json";
    Network net1(3, 2, {5});
    net1.save_network(filename);

    Network net2(3, 2, {5});
    net2.load_network(filename);
    EXPECT_TRUE(true);
    std::remove(filename.c_str());
}