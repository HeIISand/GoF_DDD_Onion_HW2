#ifndef GOF_DDD_ONION_HW2_CALCULATEFINALSCORE_H
#define GOF_DDD_ONION_HW2_CALCULATEFINALSCORE_H

#include "../Domain/Entities/Criterion.h"
#include "../Domain/Entities/Grade.h"
#include <vector>

class CalculateFinalScore {
public:
    double calculate(const std::vector<Criterion>& criterionsList, const std::vector<Grade>& studentGrades) const {
        double total = 0.0;

        for (const auto& criterion : criterionsList) {
            for (const auto& grade : studentGrades) {
                if (grade.getCriterionId() == criterion.getId()) {
                    double normalized = grade.getScore().getValue() / criterion.getMaxScore().getValue();
                    total += normalized * criterion.getWeight().getValue() * 10.0;
                    break;
                }
            }
        }

        return total;
    }
};

#endif
