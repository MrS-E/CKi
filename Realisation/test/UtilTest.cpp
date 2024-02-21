//
// Created by MrS-E on 12/02/2024.
//

#include "../Util.h"
#include <gtest/gtest.h>
#include <fstream>

class UtilTest : public ::testing::Test {
protected:
    std::string filename = "test.bin";
    void SetUp() override {
        std::ofstream file(filename, std::ios::binary);
        unsigned char testData[4] = {0x12, 0x34, 0x56, 0x78};
        file.write(reinterpret_cast<char*>(testData), sizeof(testData));
        file.close();
    }

    void TearDown() override {
        std::remove(filename.c_str());
    }
};

TEST_F(UtilTest, SigmoidReturnsExpectedValue) {
    double input = 0.0;
    double expected_output = 0.5;
    double output = Util::sigmoid(input);
    EXPECT_NEAR(output, expected_output, 1e-6);
}

TEST_F(UtilTest, SigmoidDerivativeReturnsExpectedValue) {
    double input = 0.0;
    double expected_output = 0.25;
    double output = Util::sigmoid_derivative(input);
    EXPECT_NEAR(output, expected_output, 1e-6);
}

TEST_F(UtilTest, ReadIntReadsCorrectValue) {
    std::ifstream file(filename, std::ios::binary);
    ASSERT_TRUE(file.is_open());
    int result = Util::read_int(file);
    EXPECT_EQ(result, 0x12345678);
    file.close();
}

TEST_F(UtilTest, FileNotExistsImages) {
    std::string filename = "non_existing_file";
    ASSERT_THROW(Util::read_mnist_images(filename), std::runtime_error);
}

TEST_F(UtilTest, CorrectNumberOfImages) {
    std::string filename = "../test/dummy_mnist"; //correct path to the file if built doesn't find file
    auto images = Util::read_mnist_images(filename);
    int expected_number_of_images = 10;
    ASSERT_EQ(images.size(), expected_number_of_images);
}

TEST_F(UtilTest, CorrectNormalization) {
    std::string filename = "../test/dummy_mnist"; //correct path to the file if built doesn't find file
    auto images = Util::read_mnist_images(filename);
    for (const auto& image : images) {
        for (double pixel : image) {
            ASSERT_GE(pixel, 0.0);
            ASSERT_LE(pixel, 1.0);
        }
    }
}

TEST_F(UtilTest, FileNotExistsLabels) {
    std::string filename = "non_existing_file";
    ASSERT_THROW(Util::read_mnist_labels(filename), std::runtime_error);
}

TEST_F(UtilTest, CorrectNumberOfLabels) {
    std::string filename = "../test/dummy_labels"; //correct path to the file if built doesn't find file
    auto images = Util::read_mnist_labels(filename);
    int expected_number_of_labels = 10;
    ASSERT_EQ(images.size(), expected_number_of_labels);
}

TEST_F(UtilTest, CorrectLabels) {
    std::string filename = "../test/dummy_labels"; //correct path to the file if built doesn't find file
    auto labels = Util::read_mnist_labels(filename);
    for (double label : labels) {
        ASSERT_GE(label, 0.0);
        ASSERT_LE(label, 9.0);
    }
}