#ifndef MANNA_LATTICE_HPP
#define MANNA_LATTICE_HPP

#include <algorithm>
#include <random>
#include <vector>

class manna_lattice {
public:
    typedef size_t state_t;
    typedef size_t index_t;
    typedef double float_t;
    manna_lattice(const index_t L_, const index_t nr_particles_)
        : L(L_),
          nr_particles(nr_particles_),
          state(L_, 0),
          delta(L_, 0),
          // Use binomial distribution for values larger-equal that.
          // Only affects performance (if >= 2).
          binomial_threshold(2),
          gen(42),
          real_distr(0, 1),
          int_distr(0, L_ - 1),
          alive(true)
    {}
    void reset()
    {
        state.assign(L, 0);
        for (index_t i = 0; i < nr_particles; ++i) {
            ++state[int_distr(gen)];
        }
        alive = true;
    }
    void take_step(index_t nr_steps)
    {
        for (index_t i = 0; i < nr_steps; ++i) {
            take_step();
        }
    }
    void take_step()
    {
        if (!alive) {
            return;
        }
        move_particles_to_delta();
        move_delta_to_state();
    }
    void move_particles_to_delta()
    {
        delta.assign(L, 0);
        alive = false;
        for (index_t i = 0; i < L; ++i) {
            const state_t nr_particles_on_site = state[i];
            if (nr_particles_on_site >= binomial_threshold) {
                alive = true;
                distribute_binomial(i);
            }
            else if (nr_particles_on_site >= 2) {
                alive = true;
                distribute_sequential(i);
            }
        }
    }
    void distribute_sequential(const index_t site_index)
    {
        const state_t nr_particles_to_move = state[site_index];
        state[site_index] = 0;
        for (index_t i = 0; i < nr_particles_to_move; ++i) {
            if (real_distr(gen) < 0.5) {
                ++delta[left(site_index)];
            }
            else {
                ++delta[right(site_index)];
            }
        }
    }
    void distribute_binomial(const index_t site_index)
    {
        const state_t nr_particles_to_move = state[site_index];
        state[site_index] = 0;
        const index_t nr_move_to_left = std::binomial_distribution<index_t>{nr_particles_to_move, 0.5}(gen);
        delta[left(site_index)] += nr_move_to_left;
        delta[right(site_index)] += (nr_particles_to_move - nr_move_to_left);
    }
    void move_delta_to_state()
    {
        for (index_t i = 0; i < L; ++i) {
            state[i] += delta[i];
        }
    }
    float_t order_parameter() const
    {
        index_t nr_active_lattice_sites = 0;
        return static_cast<float_t>(std::count_if(state.begin(), state.end(), [](const state_t s) { return s >= 2; })) / static_cast<float_t>(L);
    }
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
    std::uniform_real_distribution<float_t> real_distr;
    std::uniform_int_distribution<index_t> int_distr;
    bool alive;
};

#endif // #ifndef MANNA_LATTICE_HPP
