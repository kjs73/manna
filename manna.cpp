#include "manna.hpp"

manna::manna()
    : nr_samples("nr_samples", std::cin, std::cout),
      lattice_size("lattice_size", std::cin, std::cout),
      nr_steps("nr_steps", std::cin, std::cout),
      record_every("record_every", std::cin, std::cout)
{
    if (nr_samples() == 0 || lattice_size() < 4 || nr_steps() % record_every()) {
        throw std::runtime_error("manna: illegal input");
    }
    run();
}

void manna::run()
{
    for (index_t i = 0; i < nr_samples(); ++i) {
        simulate_sample();
    }
}

void manna::simulate_sample()
{
    
}

void manna::print_results()
{
    std::cout << "Fixed energy Manna model\n";
}
