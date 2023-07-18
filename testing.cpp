#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h" //doctest version is "2.4.11"
#include <cassert>
#include <cmath>
#include <limits>
#include <string>
#include <vector>

struct State {
  double s;
  double i;
  double r;

  State(double sus, double inf, double rec) : s{sus}, i{inf}, r{rec} {
    assert(s > 0 || s == 0);
    assert(i > 0 || i == 0);
    assert(r > 0 || r == 0);
  };
  State() {
    s = 0.;
    i = 0.;
    r = 0.;
  }
};

class Disease {
public:
  std::string name_;
  std::vector<State> state_;
  double tot_;
  double gamma_;
  double beta_;

  auto evolve_(State const &begin) {
    auto end = State();
    end.s = begin.s - beta_ * begin.i * begin.s;
    if (end.s < 0) {
      end.s = 0;
    }
    end.r = begin.r + gamma_ * begin.i;
    if (end.r > tot_) {
      end.r = tot_;
    }
    end.i = begin.i + beta_ * begin.i * begin.s - gamma_ * begin.i;
    if (end.i > tot_) {
      end.i = tot_ - end.r - end.s;
    }
    
    assert(!(end.s < 0));
    assert(!(end.i < 0));
    assert(!(end.r < 0));
    return end;
  };

  Disease(std::string p, int n, double inf, double b, double y) : name_{p} {
    assert(b > 0 && b < 1);
    assert(y > 0 && y < 1);
    assert(n > 1);

    tot_ = n;
    beta_ = b / tot_;
    gamma_ = y;
    State state_0{(double)n - inf, inf, 0.};
    state_.push_back(state_0);
  }

  void evolve(int n) {
    assert(n > 0);

    for (int i = 0; i < n; ++i) {
      state_.push_back(evolve_(state_[i]));
    }
  }
};

//////////////DISEASE TEST//////////////

TEST_CASE("Testing State") {
  auto a = State(1e6, 0, 1);
  CHECK(a.s == 1e6);
  CHECK(a.i == 0);
  CHECK(a.r == 1);
  auto b = State();
  CHECK(b.s == 0);
  CHECK(b.i == 0);
  CHECK(b.r == 0);
}

TEST_CASE("Testing Disease") {
  auto d = Disease("nome", 500, 5, 0.3, 0.2);
  CHECK(d.state_[0].s == 495);
  CHECK(d.state_[0].i == 5);
  CHECK(d.state_[0].r == 0);
  CHECK(d.beta_ == 6e-4);
  CHECK(d.gamma_ == 0.2);
  // test function evolve
  d.evolve(1);
  CHECK((int)d.state_[1].s == 493);
  CHECK((int)d.state_[1].i == 5);
  CHECK((int)d.state_[1].r == 1);
  d.evolve(2);
  CHECK((int)d.state_[1].s == 493);
  CHECK((int)d.state_[1].i == 5);
  CHECK((int)d.state_[1].r == 1);
}
