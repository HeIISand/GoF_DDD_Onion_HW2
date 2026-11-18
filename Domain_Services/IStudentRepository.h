#ifndef GOF_DDD_ONION_HW2_ISTUDENTREPOSITORY_H
#define GOF_DDD_ONION_HW2_ISTUDENTREPOSITORY_H

#include "../Domain/Entities/Student.h"
#include <vector>
#include <optional>

class IStudentRepository {
public:
    virtual ~IStudentRepository() = default;
    virtual void add(const Student& student) = 0;
    virtual std::optional<Student> getById(int id) const = 0;
    virtual std::vector<Student> getAll() const = 0;
    virtual int getNextId() = 0;
};

#endif
