#ifndef GOF_DDD_ONION_HW2_STUDENTREPOSITORY_H
#define GOF_DDD_ONION_HW2_STUDENTREPOSITORY_H

#include "../Domain_Services/IStudentRepository.h"
#include <vector>
#include <optional>

class StudentRepository : public IStudentRepository {
private:
    std::vector<Student> students;
    int nextId = 1;

public:
    void add(const Student& student) override {
        students.push_back(student);
    }

    std::optional<Student> getById(int id) const override {
        for (const auto& s : students) {
            if (s.getId() == id) {
                return s;
            }
        }
        return std::nullopt;
    }

    std::vector<Student> getAll() const override {
        return students;
    }

    int getNextId() override {
        return nextId++;
    }
};

#endif
