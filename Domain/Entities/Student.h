#ifndef GOF_DDD_ONION_HW2_STUDENT_H
#define GOF_DDD_ONION_HW2_STUDENT_H

#include "../Value_Objects/Name.h"
#include <stdexcept>
#include <utility>

class Student {
private:
    int id;
    Name name;

public:
    Student(int id, Name name) : id(id), name(std::move(name)) {
        if (id <= 0) {
            throw std::invalid_argument("ID студента должен быть положительным.");
        }
    }

    int getId() const { return id; }
    const Name& getName() const { return name; }
};

#endif
