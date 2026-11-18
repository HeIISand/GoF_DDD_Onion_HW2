#ifndef GOF_DDD_ONION_HW2_SCORE_H
#define GOF_DDD_ONION_HW2_SCORE_H

#include <stdexcept>

class Score {
private:
    double value;

public:
    explicit Score(double val) : value(val) {
        if (value < 0.0) {
            throw std::invalid_argument("Балл не может быть отрицательным.");
        }
    }

    double getValue() const { return value; }

    bool operator<=(const Score& other) const {
        return value <= other.value;
    }
};

#endif
