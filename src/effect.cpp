

#include "effect.hpp"
#include "rng.hpp"


bool IsDamageType(EffectType type)
{
  return type == EffectType::Damage
    || type == EffectType::DoT;
}

bool IsHealType(EffectType type)
{
  return type == EffectType::Heal;
}


VariableDamage::VariableDamage(int base, int step)
  :
  InstantEffect{ EffectType::Damage },
  base_{ base },
  step_{ step }
{}

VariableDamage::VariableDamage(int base)
  :
  InstantEffect{ EffectType::Damage },
  base_{ base },
  step_{ 10 }
{}

int VariableDamage::strength_() const
{
  return base_ + rng::DamageRoll(step_);
}


FlatDamage::FlatDamage(int damage)
  :
  InstantEffect{ EffectType::Damage },
  damage_{ damage }
{}


Heal::Heal(int heal)
  :
  InstantEffect{ EffectType::Heal },
  heal_{ heal }
{}


OverTimeEffect::OverTimeEffect(int strength, int turns, EffectType type)
  :
  CardEffect{ type },
  strength{ strength },
  turns{ turns }
{}


DoT::DoT(int damage, int turns)
  : OverTimeEffect{ damage, turns, EffectType::DoT }
{}

DoT::DoT(int damage)
  : OverTimeEffect{ damage, 3, EffectType::DoT }
{}

HoT::HoT(int heal, int turns)
  : OverTimeEffect{ heal, turns, EffectType::HoT }
{}

HoT::HoT(int heal)
  : OverTimeEffect{ heal, 3, EffectType::HoT }
{}


Charm::Charm(int strength, CharmType type)
  :
  CardEffect{ EffectType::Charm },
  strength{ strength },
  type{ type }
{}


HangingOverTime::HangingOverTime(const OverTimeEffect& base, EffectType type)
  :
  type{ type },
  per_turn{ base.strength / base.turns },
  turns_left{ base.turns }
{}

HangingDoT::HangingDoT(const DoT& base)
  : HangingOverTime{ base, EffectType::DoT }
{}

HangingHoT::HangingHoT(const HoT& base)
  : HangingOverTime{ base, EffectType::HoT }
{}
