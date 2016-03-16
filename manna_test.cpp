//http://www.ibm.com/developerworks/aix/library/au-ctools1_boost/
#define BOOST_TEST_MODULE Manna Test

#include <sstream>

#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/test/included/unit_test.hpp>

#include "manna.hpp"
#include "precise_output.hpp"

BOOST_AUTO_TEST_CASE(variable_test)
{
    variable v;
    v.add(2);
    v.add(-1);
    v.add(-1);
    BOOST_CHECK(v.mean() == 0);
    v = variable();
    std::mt19937_64 gen(42);
    const double xmin = -12.12;
    const double xmax = 42.42;
    const size_t samples = 100000;
    for (size_t i = 0; i < samples; ++i) {
        v.add(std::uniform_real_distribution<double>{xmin, xmax}(gen));
    }
    const double true_mean = 0.5 * (xmax + xmin);
    BOOST_CHECK_CLOSE(true_mean, v.mean(), 1);
    const double true_variance = std::pow(xmax - xmin, 2) / 12;
    BOOST_CHECK_CLOSE(true_variance, std::pow(v.error(), 2) * (samples - 1), 1);
}

BOOST_AUTO_TEST_CASE(output_test)
{
    // http://www.cplusplus.com/reference/string/string/string/
    BOOST_CHECK_THROW(precise_output<double>(std::string(NAME_MAX + 1, 42)), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(parameter_test)
{
    std::stringstream is("42.42");
    parameter<double> tp("test parameter", is, std::cout);
    BOOST_CHECK_CLOSE(42.42, tp(), 1e-10);
}

BOOST_AUTO_TEST_CASE(lattice_test)
{
    const size_t L = 42;
    const size_t N = 100000;
    manna_lattice lattice(L, N);
    for (size_t i = 0; i < L; ++i) {
        BOOST_CHECK((i + 1) % L == lattice.right(i));
        if (i) {
            BOOST_CHECK((i - 1) == lattice.left(i));
        }
        else {
            BOOST_CHECK(L - 1 == lattice.left(i));
        }
    }
    BOOST_CHECK_CLOSE(lattice.order_parameter(), 0, 1e-10);
    lattice.reset();
    BOOST_CHECK_CLOSE(lattice.order_parameter(), 1, 1e-10);
    manna_lattice subcritical_lattice(L, 0.5 * L);
    subcritical_lattice.reset();
    BOOST_CHECK(subcritical_lattice.order_parameter() > 0);
    subcritical_lattice.take_step(10 * L);
    BOOST_CHECK_CLOSE(subcritical_lattice.order_parameter(), 0, 1e-10);
    lattice.take_step(10 * L);
    BOOST_CHECK_CLOSE(lattice.order_parameter(), 1, 1e-10);
}
