#ifndef MANNA_HPP_KJS
#define MANNA_HPP_KJS

#include <memory>
#include <vector>

#include "parameter.hpp"
#include "variable.hpp"

class manna {
public:
    typedef size_t index_t;
    typedef double float_t;
    manna();
    void run();
    void simulate_sample();
    void print_results();
private:
    // Input
    parameter<index_t> nr_samples;
    parameter<index_t> lattice_size;
    parameter<index_t> nr_steps;
    parameter<index_t> record_every;
    // Output
    std::vector<std::shared_ptr<variable> > order_parameter;
};

#endif // #ifndef MANNA_HPP_KJS
