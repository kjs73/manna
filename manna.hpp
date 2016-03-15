#ifndef MANNA_HPP_KJS
#define MANNA_HPP_KJS

#include <memory>

#include "manna_lattice.hpp"
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
    // input
    parameter<index_t> nr_samples;
    parameter<index_t> lattice_size;
    parameter<index_t> nr_steps;
    parameter<index_t> record_every;
    parameter<float_t> number_density;
    // output
    std::vector<std::shared_ptr<variable> > order_parameter;
    // state
    manna_lattice lattice;
};

#endif // #ifndef MANNA_HPP_KJS
