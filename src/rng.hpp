#pragma once

#include <random>


namespace rng {

  int PercentChance(int chance);
  int DamageRoll(int step);
  bool CoinToss();

  template <typename T>
  std::pair<T, T> RandomOrder(T first, T second)
  {
    if (CoinToss())
      return std::make_pair(first, second);
    else
      return std::make_pair(second, first);
  }

}
