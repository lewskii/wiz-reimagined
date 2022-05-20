

#include "effect.hpp"
#include "rng.hpp"


namespace Effect {

  VariableDamage::VariableDamage(int base, int increment)
    :
    Effect{ Type::Damage },
    base_{ base },
    increment_{ increment }
  {}

  VariableDamage::VariableDamage(int base)
    :
    Effect{ Type::Damage },
    base_{ base },
    increment_{ 10 }
  {}

  int VariableDamage::strength() const
  {
    return base_ + rng::DamageRoll() * increment_;
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

}
