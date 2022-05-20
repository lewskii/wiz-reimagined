#pragma once

#include <string>
#include <vector>

#include "effect.hpp"


class Card {
public:
  Card(
    const std::string name,
    const int accuracy,
    const int pip_cost,
    const std::initializer_list<Effect::Effect*> effects
  )
    :
    name{ name },
    accuracy{ accuracy },
    pip_cost{ pip_cost },
    effects{ effects }
  {}

  const std::string name;
  const int accuracy;
  const int pip_cost;
  const std::vector<Effect::Effect*> effects;
};