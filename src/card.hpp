#pragma once

#include <memory>
#include <string>
#include <vector>

#include "effect.hpp"



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
    needs_ally_target{ HasTarget(effects, Target::Ally) },
    needs_enemy_target{ HasTarget(effects, Target::Enemy) }
  {}

  bool HasDamage() const;
  bool HasHealing() const;

  const std::string name;
  const School school;
  const int accuracy;
  const int pip_cost;
  const std::vector<EffectPtr> effects;
  const bool needs_ally_target;
  const bool needs_enemy_target;

private:
  static bool HasTarget(
    std::initializer_list<EffectPtr> effects, Target target
  );
};