#ifndef GOF_DDD_ONION_HW2_CRITERIONSLISTBUILDER_H
#define GOF_DDD_ONION_HW2_CRITERIONSLISTBUILDER_H

#include "Entities/Criterion.h"
#include <vector>
#include <string>
#include <stdexcept>

class CriterionsListBuilder {
private:
    std::vector<Criterion> criterions;
    int nextId = 1;

public:
    explicit CriterionsListBuilder(int startId = 1) : nextId(startId) {}

    CriterionsListBuilder& addCriterion(const std::string& title, double maxScore, double weight) {
        criterions.emplace_back(nextId++, title, Score(maxScore), Weight(weight));
        return *this;
    }

    std::vector<Criterion> build() const {
        if (criterions.empty()) {
            throw std::invalid_argument("Список критериев не может быть пустым.");
        }

        double totalWeight = 0.0;
        for (const auto& c : criterions) {
            totalWeight += c.getWeight().getValue();
        }

        if (totalWeight > 1.0) {
            throw std::invalid_argument("Сумма весов критериев не может превышать 1.0.");
        }

        return criterions;
    }
};

#endif
