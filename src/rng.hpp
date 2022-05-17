#pragma once

#include <random>


namespace rng {
  std::mt19937 rng{ std::random_device{}() };
  std::uniform_int_distribution acc_roll{ 1, 100 };
  std::uniform_int_distribution damage_roll{ 0, 4 };
}