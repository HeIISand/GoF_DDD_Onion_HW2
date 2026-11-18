#ifndef GOF_DDD_ONION_HW2_WEIGHT_H
#define GOF_DDD_ONION_HW2_WEIGHT_H

#include <stdexcept>

class Weight {
private:
    double value;

public:
    explicit Weight(double val) : value(val) {
        if (value <= 0.0 || value > 1.0) {
            throw std::invalid_argument("Вес критерия должен быть в диапазоне (0, 1]");
        }
    }

    double getValue() const { return value; }
};

#endif
