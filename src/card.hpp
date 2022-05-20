#pragma once

#include <string>
#include <vector>

#include "effect.hpp"


class Card {
public:
  typedef std::shared_ptr<Effect::Effect> EffectPtr;

  Card(
    const std::string name,
    const int accuracy,
    const int pip_cost,
    const std::initializer_list<EffectPtr> effects
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
  const std::vector<EffectPtr> effects;
};