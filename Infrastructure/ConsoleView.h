#ifndef GOF_DDD_ONION_HW2_CONSOLEVIEW_H
#define GOF_DDD_ONION_HW2_CONSOLEVIEW_H

#include "IView.h"
#include <iostream>
#include <string>

class StandardConsoleView : public IView {
public:
    void print(const std::string& message) const override {
        std::cout << message << std::endl;
    }

    int readInt() const override {
        std::string input;
        while (true) {
            std::cin >> input;
            try {
                return std::stoi(input);
            }
            catch (...) {
                std::cout << "Ошибка. Попробуйте еще раз:\n";
            }
        }
    }

    double readDouble() const override {
        std::string input;
        while (true) {
            std::cin >> input;
            try {
                return std::stod(input);
            }
            catch (...) {
                std::cout << "Ошибка. Попробуйте еще раз:\n";
            }
        }
    }

    std::string readString() const override {
        std::string input;
        std::getline(std::cin >> std::ws, input);
        return input;
    }
};

#endif
