#include "manna_lattice.hpp"

manna_lattice::manna_lattice(const index_t L_, const index_t nr_particles_)
    : L(L_),
      nr_particles(nr_particles_),
      state(L_, 0),
      delta(L_, 0),
      gen(42),
      int_distr(0, L_ - 1),
      alive(true)
{}
        
void manna_lattice::reset()
{
    state.assign(L, 0);
    for (index_t i = 0; i < nr_particles; ++i) {
        ++state[int_distr(gen)];
    }
    alive = true;
}

void manna_lattice::take_step(const index_t nr_steps)
{
    for (index_t i = 0; i < nr_steps; ++i) {
        take_step();
    }
}

void manna_lattice::take_step()
{
    if (!alive) {
        return;
    }
    move_particles_to_delta();
    move_delta_to_state();
}

void manna_lattice::move_particles_to_delta()
{
    delta.assign(L, 0);
    alive = false;
    for (index_t i = 0; i < L; ++i) {
        const state_t nr_particles_on_site = state[i];
        if (nr_particles_on_site >= 2) {
            alive = true;
            distribute_binomial(i);
        }
    }
}

void manna_lattice::distribute_binomial(const index_t site_index)
{
    const state_t nr_particles_to_move = state[site_index];
    state[site_index] = 0;
    const index_t nr_move_to_left = std::binomial_distribution<index_t>{nr_particles_to_move, 0.5}(gen);
    delta[left(site_index)] += nr_move_to_left;
    delta[right(site_index)] += (nr_particles_to_move - nr_move_to_left);
}

void manna_lattice::move_delta_to_state()
{
    for (index_t i = 0; i < L; ++i) {
        state[i] += delta[i];
    }
}

manna_lattice::float_t manna_lattice::order_parameter() const
{
    index_t nr_active_lattice_sites = 0;
    return static_cast<float_t>(std::count_if(state.begin(), state.end(), [](const state_t s) { return s >= 2; })) / static_cast<float_t>(L);
}
