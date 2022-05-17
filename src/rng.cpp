

#include <random>
#include "rng.hpp"

namespace rng {
  namespace {
    std::random_device rd;
    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    static std::mt19937 rng{ ss };

    static const std::uniform_int_distribution acc_roll{ 1, 100 };
    static const std::uniform_int_distribution damage_roll{ 0, 4 };
  }

  int AccRoll() {
    return acc_roll(rng);
  }

  int DamageRoll() {
    return damage_roll(rng);
  }

}