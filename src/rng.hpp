#pragma once

#include <random>


namespace rng {
  static std::mt19937 rng{ std::random_device{}() };
  static const std::uniform_int_distribution acc_roll{ 1, 100 };
  static const std::uniform_int_distribution damage_roll{ 0, 4 };
}
