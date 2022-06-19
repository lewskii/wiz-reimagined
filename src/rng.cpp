

#include <random>
#include "rng.hpp"

namespace rng {
  namespace {
    std::random_device rd;
    const std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    std::mt19937 rng{ ss };

    const std::uniform_int_distribution percent{ 0, 99 };
    const std::uniform_int_distribution damage_roll{ 0, 4 };
  }

  int PercentChance(int chance) {
    return percent(rng) < chance;
  }

  int DamageRoll(int step) {
    return damage_roll(rng) * step;
  }

  bool CoinToss()
  {
    return PercentChance(50);
  }

}