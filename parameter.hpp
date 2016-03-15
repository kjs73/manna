#ifndef PARAMETER_HPP_KJS
#define PARAMETER_HPP_KJS

#include <iostream>
#include <string>

template <class T>
class parameter {
public:
    parameter(const std::string name__, std::istream& istm, std::ostream& ostm)
        : name_(name__)
    {
        read(istm, ostm);
    }
    void read(std::istream& istm, std::ostream& ostm)
    {
        ostm << "provide parameter " << name() << "\n";
        istm >> value_;
    }
    std::string name() const
    {
        return name_;
    }
    T operator()() const
    {
        return value_;
    }
private:
    const std::string name_;
    T value_;
};

#endif // #ifndef PARAMETER_HPP_KJS
