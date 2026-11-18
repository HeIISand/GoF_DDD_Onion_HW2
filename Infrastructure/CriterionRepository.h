#ifndef GOF_DDD_ONION_HW2_CRITERIONREPOSITORY_H
#define GOF_DDD_ONION_HW2_CRITERIONREPOSITORY_H

#include "../Domain_Services/ICriterionRepository.h"
#include <vector>
#include <optional>

class CriterionRepository : public ICriterionRepository {
private:
    std::vector<Criterion> criterions;
    int nextId = 1;

public:
    void add(const Criterion& criterion) override {
        if (criterion.getId() >= nextId) {
            nextId = criterion.getId() + 1;
        }
        criterions.push_back(criterion);
    }

    bool remove(int id) override {
        for (auto it = criterions.begin(); it != criterions.end(); ++it) {
            if (it->getId() == id) {
                criterions.erase(it);
                return true;
            }
        }
        return false;
    }

    std::optional<Criterion> getById(int id) const override {
        for (const auto& c : criterions) {
            if (c.getId() == id) {
                return c;
            }
        }
        return std::nullopt;
    }

    std::vector<Criterion> getAll() const override {
        return criterions;
    }

    double getTotalWeight() const override {
        double total = 0.0;
        for (const auto& c : criterions) {
            total += c.getWeight().getValue();
        }
        return total;
    }

    int getNextId() override {
        return nextId++;
    }
};

#endif
