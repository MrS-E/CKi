//
// Created by simeo on 25/01/2024.
//
#include <iostream>
#include "Network.h"
#include "Util.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <sstream>

using namespace ftxui;

void train(Network &nn) {
    std::cout << std::endl << "Training..." << std::endl;
    std::cout << "Reading MNIST data..." << std::endl;
    std::vector<std::vector<double>> training_inputs = Util::read_mnist_training_images("../datasets");
    std::vector<std::vector<double>> training_labels = Util::read_mnist_training_labels("../datasets");

    std::cout << "Training..." << std::endl;
    nn.train(training_inputs, training_labels, 1, 0.01);

    std::cout << "Saving weights..." << std::endl;
    std::cout << "Done!" << std::endl;
}

double verif(Network &nn) {
    std::cout << std::endl << "Testing..." << std::endl;
    std::cout << "Reading MNIST data..." << std::endl;
    std::vector<std::vector<double>> test_inputs = Util::read_mnist_test_images("../datasets");
    std::vector<std::vector<double>> test_labels = Util::read_mnist_test_labels("../datasets");

    std::cout << "Testing..." << std::endl;
    double acc = nn.verify(test_inputs, test_labels);
    std::cout << "Accuracy: " << acc << std::endl;
    std::cout << "Done!" << std::endl;
    return acc;
}

std::vector<std::wstring> splitLines(const std::wstring &text) {
    std::wstringstream wss(text);
    std::vector<std::wstring> lines;
    std::wstring line;

    while (std::getline(wss, line, L'\n')) {
        lines.push_back(line);
    }

    return lines;
}

int main() {
    Network nn(784, 10, {32, 16});

    int progress = 0;
    int max_progress = 100;
    std::wstring log = L"Log initialized.\n";

    auto log_component = Renderer([&] { //FIXME still bugy
        std::vector<Element> elements;
        auto lines = splitLines(log);
        elements.reserve(lines.size());
        for (auto &line: lines) {
            elements.push_back(text(line));
        }
        return vbox(elements);
    });

    auto loading_bar = Renderer([&] {
        return hbox({
            text(L"Progress: "),
            gauge(progress / max_progress)
        });
    });

    auto button1 = Button("Train", [&] {
        progress = 0;
        std::vector<std::vector<double>> training_inputs = Util::read_mnist_training_images("../mnist");
        std::vector<std::vector<double>> training_labels = Util::read_mnist_training_labels("../mnist");
        nn.train(training_inputs, training_labels, 1, 0.01, [&](int i, int max) {
            progress = i;
            max_progress = max;
        }, [&](double error) {
            log += L"Error: " + std::to_wstring(error) + L"\n";
        });

    });
    auto button2 = Button("Verify", [&] {

    });

    auto container = Container::Vertical({
        button1,
        button2,
        loading_bar,
        log_component,
    });

    // ScreenInteractive
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(container);

    return 0;
}
