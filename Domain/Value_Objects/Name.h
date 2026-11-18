#ifndef GOF_DDD_ONION_HW2_NAME_H
#define GOF_DDD_ONION_HW2_NAME_H

#include <string>
#include <stdexcept>
#include <utility>

class Name {
private:
    std::string firstName;
    std::string lastName;

public:
    Name(std::string first, std::string last) : firstName(std::move(first)), lastName(std::move(last)) {
        if (firstName.empty() || lastName.empty()) {
            throw std::invalid_argument("Имя и фамилия не могут быть пустыми.");
        }
    }

    const std::string& getFirstName() const { return firstName; }
    const std::string& getLastName() const { return lastName; }

    std::string getFullName() const {
        return firstName + " " + lastName;
    }
};

#endif
