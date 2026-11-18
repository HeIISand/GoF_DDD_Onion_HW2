#ifndef GOF_DDD_ONION_HW2_CRITERION_H
#define GOF_DDD_ONION_HW2_CRITERION_H

#include "../Value_Objects/Score.h"
#include "../Value_Objects/Weight.h"
#include <string>
#include <stdexcept>
#include <utility>

class Criterion {
private:
    int id;
    std::string title;
    Score maxScore;
    Weight weight;

public:
    Criterion(int id, std::string criterionTitle, Score max, Weight w)
        : id(id), title(std::move(criterionTitle)), maxScore(max), weight(w) {
        if (id <= 0) {
            throw std::invalid_argument("ID критерия должен быть положительным.");
        }
        if (title.empty()) {
            throw std::invalid_argument("Название критерия не может быть пустым.");
        }
        if (maxScore.getValue() <= 0.0) {
            throw std::invalid_argument("Максимальный балл критерия должен быть больше нуля.");
        }
    }

    int getId() const { return id; }
    const std::string& getTitle() const { return title; }
    const Score& getMaxScore() const { return maxScore; }
    const Weight& getWeight() const { return weight; }
};

#endif
