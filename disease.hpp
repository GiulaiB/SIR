#ifndef DISEASE_HPP
#define DISEASE_HPP

#include <vector>

#include "structure.hpp"

namespace disease {
    class Disease {
    private:
        std::string name_;
        std::vector<State> state_;
        double tot_;
        double gamma_;
        double beta_;

    public:
        Disease(std::string p, int n, double inf, double b, double y);

        //evolving the State of the private vector
        State evolve_(State const& begin);

        //creating day by day the state_
        void evolve(int n);

        //printing the table on the standard output
        void print();

        //printing the table on file
        void f_print();
 
    };
}

#endif
