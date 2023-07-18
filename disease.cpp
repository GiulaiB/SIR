#include <cassert>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include "disease.hpp"


//evolution of the disease
using namespace std;

State disease::Disease::evolve_(State const &begin) {
  auto end = State();
  end.s = begin.s - beta_ * begin.i * begin.s; //equation 3a
  if (end.s < 0) {
    end.s = 0;
  }
  end.r = begin.r + gamma_ * begin.i; //equation 3b
  if (end.r > tot_) {
    end.r = tot_;
  }
  end.i = begin.i + beta_ * begin.i * begin.s - gamma_ * begin.i; //equation 3c
  if (end.i > tot_) {
    end.i = tot_ - end.r - end.s;
  }
  
  assert(!(end.s < 0));
  assert(!(end.i < 0));
  assert(!(end.r < 0));
  return end;
};

disease::Disease::Disease(string p, int n, double inf, double b, double y) : name_{p} {
  assert(b > 0 && b < 1);
  assert(y > 0 && y < 1);
  assert(n > 1);

  tot_ = n;
  beta_ = b / tot_;
  gamma_ = y * 0.1;
  State state_0{(double)n - inf, inf, 0.};
  state_.push_back(state_0);
}

void disease::Disease::evolve(int n) {
  for (int i = 0; i < n; ++i) {
    state_.push_back(evolve_(state_[i]));
  }
}

//printing the results
void disease::Disease::print() {
  int i = 0;
  auto tab = setw(15);
  cout << "Disease name: " << name_ << '\n';
  cout << "Current value of R0: " << (tot_ * beta_) / gamma_ << '\n'; //R0
  cout << tab << "Day" << tab << "Susceptible" << tab << "Infectuos" << tab
            << "Recovered" << '\n';
  for (auto const it : state_) {
    cout << setprecision(10) << tab << i << tab << (int)it.s << tab
              << (int)it.i << tab << (int)it.r << '\n';
    ++i;
  }
}

//saving the results in "epidemic.txt"
void disease::Disease::f_print() { 
  streambuf *backup = cout.rdbuf();
  ofstream fp;
  fp.open("epidemic.txt");
  cout.rdbuf(fp.rdbuf());
  print();
  fp.close();
  cout.rdbuf(backup);
}
