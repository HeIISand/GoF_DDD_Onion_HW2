#ifndef GOF_DDD_ONION_HW2_GRADEREPOSITORY_H
#define GOF_DDD_ONION_HW2_GRADEREPOSITORY_H

#include "../Domain_Services/IGradeRepository.h"
#include <vector>
#include <optional>

class GradeRepository : public IGradeRepository {
private:
    std::vector<Grade> grades;
    int nextId = 1;

public:
    void save(const Grade& grade) override {
        for (auto& existing : grades) {
            if (existing.getStudentId() == grade.getStudentId() &&
                existing.getCriterionId() == grade.getCriterionId()) {
                existing = grade;
                return;
            }
        }
        grades.push_back(grade);
    }

    bool remove(int studentId, int criterionId) override {
        for (auto it = grades.begin(); it != grades.end(); ++it) {
            if (it->getStudentId() == studentId && it->getCriterionId() == criterionId) {
                grades.erase(it);
                return true;
            }
        }
        return false;
    }

    void removeByCriterionId(int criterionId) override {
        for (auto it = grades.begin(); it != grades.end();) {
            if (it->getCriterionId() == criterionId) {
                it = grades.erase(it);
            } else {
                ++it;
            }
        }
    }

    std::optional<Grade> getByStudentAndCriterion(int studentId, int criterionId) const override {
        for (const auto& g : grades) {
            if (g.getStudentId() == studentId && g.getCriterionId() == criterionId) {
                return g;
            }
        }
        return std::nullopt;
    }

    std::vector<Grade> getByStudentId(int studentId) const override {
        std::vector<Grade> result;
        for (const auto& g : grades) {
            if (g.getStudentId() == studentId) {
                result.push_back(g);
            }
        }
        return result;
    }

    std::vector<Grade> getAll() const override {
        return grades;
    }

    int getNextId() override {
        return nextId++;
    }
};

#endif
