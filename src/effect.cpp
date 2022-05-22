

#include "effect.hpp"
#include "rng.hpp"


namespace Effect {

  VariableDamage::VariableDamage(int base, int step)
    :
    Effect{ Type::Damage },
    base_{ base },
    step_{ step }
  {}

  VariableDamage::VariableDamage(int base)
    :
    Effect{ Type::Damage },
    base_{ base },
    step_{ 10 }
  {}

  int VariableDamage::strength() const
  {
    return base_ + rng::DamageRoll(step_);
  }


  FlatDamage::FlatDamage(int damage)
    :
    Effect{ Type::Damage },
    damage_{ damage }
  {}


  Heal::Heal(int heal)
    :
    Effect{ Type::Heal },
    heal_{ heal }
  {}


  OverTime::OverTime(int strength, int turns, Type type)
    :
    Effect{ type },
    strength_{ strength },
    turns_{ turns }
  {}


  DoT::DoT(int damage, int turns)
    : OverTime{ damage, turns, Type::DoT }
  {}

  DoT::DoT(int damage)
    : OverTime{ damage, 3, Type::DoT }
  {}



  HangingOverTime::HangingOverTime(OverTime& base)
    :
    per_turn{ base.strength_ / base.turns_ },
    turns_left{ base.turns_ }
  {}

  HangingDoT::HangingDoT(DoT& base)
    : HangingOverTime{ base }
  {}

}
