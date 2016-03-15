#ifndef VARIABLE_HPP_KJS
#define VARIABLE_HPP_KJS

#include <cmath>

class variable {
public:
    typedef size_t index_t;
    typedef long double float_t;
    variable()
        : nr_samples_(0),
          mean_(0),
          mean2_(0)
    {}
    void add(const float_t input)
    {
        mean_ = (mean_ * nr_samples_ + input) / (nr_samples_ + 1);
        mean2_ = (mean2_ * nr_samples_ + (input * input)) / (nr_samples_ + 1);
        ++nr_samples_;
    }
    float_t mean() const
    {
        return mean_;
    }
    float_t error() const
    {
        return std::sqrt((mean2_ - mean_ * mean_) / (nr_samples_ - 1));
    }
private:
    index_t nr_samples_;
    float_t mean_;
    float_t mean2_;
};

#endif // #ifndef VARIABLE_HPP_KJS
