#pragma once

#include <memory>
#include <string>
#include <vector>

#include "effect.hpp"


enum class TargetSelection {
  None,
  Ally,
  Enemy
};

class Card {
public:
  typedef std::shared_ptr<CardEffect> EffectPtr;

  Card(
    const std::string name,
    const School school,
    const int accuracy,
    const int pip_cost,
    const std::initializer_list<EffectPtr> effects
  )
    :
    name{ name },
    school{ school },
    accuracy{ accuracy },
    pip_cost{ pip_cost },
    effects{ effects },
    target{ DetermineTarget(effects) }
  {}

  bool HasDamage() const;
  bool HasHealing() const;

  const std::string name;
  const School school;
  const int accuracy;
  const int pip_cost;
  const std::vector<EffectPtr> effects;
  const TargetSelection target;

private:
  static TargetSelection DetermineTarget(std::initializer_list<EffectPtr> effects);
};