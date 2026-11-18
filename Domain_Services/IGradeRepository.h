#ifndef GOF_DDD_ONION_HW2_IGRADEREPOSITORY_H
#define GOF_DDD_ONION_HW2_IGRADEREPOSITORY_H

#include "../Domain/Entities/Grade.h"
#include <vector>
#include <optional>

class IGradeRepository {
public:
    virtual ~IGradeRepository() = default;
    virtual void save(const Grade& grade) = 0;
    virtual bool remove(int studentId, int criterionId) = 0;
    virtual void removeByCriterionId(int criterionId) = 0;
    virtual std::optional<Grade> getByStudentAndCriterion(int studentId, int criterionId) const = 0;
    virtual std::vector<Grade> getByStudentId(int studentId) const = 0;
    virtual std::vector<Grade> getAll() const = 0;
    virtual int getNextId() = 0;
};

#endif
