#ifndef GOF_DDD_ONION_HW2_IVIEW_H
#define GOF_DDD_ONION_HW2_IVIEW_H

#include <string>

class IView {
public:
    virtual ~IView() = default;
    virtual void print(const std::string& message) const = 0;
    virtual int readInt() const = 0;
    virtual double readDouble() const = 0;
    virtual std::string readString() const = 0;
};

#endif
