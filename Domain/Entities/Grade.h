#ifndef GOF_DDD_ONION_HW2_GRADE_H
#define GOF_DDD_ONION_HW2_GRADE_H

#include "../Value_Objects/Score.h"
#include "Criterion.h"
#include <stdexcept>

class Grade {
private:
    int id;
    int studentId;
    int criterionId;
    Score score;

public:
    Grade(int id, int studentId, int criterionId, Score score) : id(id), studentId(studentId), criterionId(criterionId), score(score) {
        if (id <= 0 || studentId <= 0 || criterionId <= 0) {
            throw std::invalid_argument("ID оценки, студента и критерия должны быть положительными.");
        }
    }

    int getId() const { return id; }
    int getStudentId() const { return studentId; }
    int getCriterionId() const { return criterionId; }
    const Score& getScore() const { return score; }

    void updateScore(const Score& newScore, const Criterion& criterion) {
        if (criterion.getId() != criterionId) {
            throw std::invalid_argument("Несоответствие критерия при обновлении оценки.");
        }
        if (!(newScore <= criterion.getMaxScore())) {
            throw std::invalid_argument("Балл превышает максимум по критерию.");
        }
        score = newScore;
    }
};

#endif
