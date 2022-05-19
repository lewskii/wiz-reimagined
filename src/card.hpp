#pragma once

#include <string>

#include "effect.hpp"


class Card {
public:
  Card(
    const std::string name,
    const int accuracy,
    const int pip_cost,
    const Effect effect
  )
    :
    name{ name },
    accuracy{ accuracy },
    pip_cost{ pip_cost },
    effect{ effect }
  {}

  const std::string name;
  const int accuracy;
  const int pip_cost;
  const Effect effect;
};