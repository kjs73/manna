#ifndef MANNA_LATTICE_HPP
#define MANNA_LATTICE_HPP

#include <random>
#include <vector>

class manna_lattice {
public:
    typedef size_t state_t;
    typedef size_t index_t;
    typedef double float_t;
    manna_lattice(const index_t, const index_t);
    void reset();
    void take_step(const index_t);
    void take_step();
    void move_particles_to_delta();
    void distribute_binomial(const index_t);
    void move_delta_to_state();
    float_t order_parameter() const;
    index_t left(const index_t center) const
    {
        if (center == 0) {
            return L - 1;
        }
        return center - 1;
    }
    index_t right(const index_t center) const
    {
        if (center == L - 1) {
            return 0;
        }
        return center + 1;
    }
private:
    const index_t L;
    const index_t nr_particles;
    std::vector<state_t> state;
    std::vector<state_t> delta;
    state_t binomial_threshold; 
    std::mt19937_64 gen;
    std::uniform_int_distribution<index_t> int_distr;
    bool alive;
};

#endif // #ifndef MANNA_LATTICE_HPP
