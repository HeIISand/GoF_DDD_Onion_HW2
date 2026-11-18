#ifndef GOF_DDD_ONION_HW2_GRADEFACTORY_H
#define GOF_DDD_ONION_HW2_GRADEFACTORY_H

#include "Entities/Grade.h"
#include "Entities/Criterion.h"
#include <vector>
#include <stdexcept>

class GradeFactory {
public:
    Grade createGrade(int id, int studentId, int criterionId, double scoreValue, const std::vector<Criterion>& criterionsList) const {
        const Criterion* foundCriterion = nullptr;
        for (const auto& criterion : criterionsList) {
            if (criterion.getId() == criterionId) {
                foundCriterion = &criterion;
                break;
            }
        }

        if (!foundCriterion) {
            throw std::invalid_argument("Критерий отсутствует в списке критериев курса.");
        }

        Score score(scoreValue);
        if (!(score <= foundCriterion->getMaxScore())) {
            throw std::invalid_argument("Балл выходит за пределы максимума критерия.");
        }

        return Grade(id, studentId, criterionId, score);
    }
};

#endif
