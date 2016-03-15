#ifndef PRECISE_OUTPUT_HPP_KJS
#define PRECISE_OUTPUT_HPP_KJS

#include <climits>
#include <fstream>
#include <limits>
#include <string>

template <class T>
class precise_output : public std::ofstream {
public:
    precise_output(std::string name)
        : std::ofstream(name.c_str())
    {
        if (name.size() > NAME_MAX) {
            throw std::runtime_error("precise_output: file name too long");
        }
        precision(std::numeric_limits<T>::digits10);
    }    
};

#endif // #ifndef PRECISE_OUTPUT_HPP_KJS
