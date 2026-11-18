#ifndef GOF_DDD_ONION_HW2_ICRITERIONREPOSITORY_H
#define GOF_DDD_ONION_HW2_ICRITERIONREPOSITORY_H

#include "../Domain/Entities/Criterion.h"
#include <vector>
#include <optional>

class ICriterionRepository {
public:
    virtual ~ICriterionRepository() = default;
    virtual void add(const Criterion& criterion) = 0;
    virtual bool remove(int id) = 0;
    virtual std::optional<Criterion> getById(int id) const = 0;
    virtual std::vector<Criterion> getAll() const = 0;
    virtual double getTotalWeight() const = 0;
    virtual int getNextId() = 0;
};

#endif
