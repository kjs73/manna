#include "manna.hpp"
#include "precise_output.hpp"
#include "progress.hpp"

manna::manna()
    : nr_samples("nr_samples", std::cin, std::cout),
      lattice_size("lattice_size", std::cin, std::cout),
      nr_steps("nr_steps", std::cin, std::cout),
      record_every("record_every", std::cin, std::cout),
      number_density("number_density", std::cin, std::cout),
      lattice(lattice_size(), std::round(number_density() * lattice_size()))
{
    if (nr_samples() == 0 || lattice_size() < 4 || nr_steps() % record_every()) {
        throw std::runtime_error("manna: illegal input");
    }
    for (index_t i = 0; i < 1 + nr_steps() / record_every(); ++i) {
        order_parameter.push_back(std::make_shared<variable>());
    }
    run();
    print_results();
}

void manna::run()
{
    progress status(nr_samples());
    for (index_t i = 0; i < nr_samples(); ++i) {
        simulate_sample();
        status.next(i);
    }
}

void manna::simulate_sample()
{
    lattice.reset();
    order_parameter[0]->add(lattice.order_parameter());
    for (index_t i = 1; i < order_parameter.size(); ++i) {
        lattice.take_step(record_every());
        order_parameter[i]->add(lattice.order_parameter());
    }
}

void manna::print_results()
{
    std::cout << "Fixed energy Manna model\n";
    precise_output<float_t> out("name.txt");
    for (index_t i = 0; i < order_parameter.size(); ++i) {
        out << i * record_every() << "\t" << order_parameter[i]->mean();
        out << "\t" << order_parameter[i]->error() << "\n";
    }
}
