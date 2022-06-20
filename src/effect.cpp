#include <iostream>

#include "effect.hpp"
#include "rng.hpp"


bool SchoolsMatch(School a, School b)
{
    return a == School::Any
      || b == School::Any
      || a == b;
}

bool IsDamageType(EffectType type)
{
  return type == EffectType::Damage
    || type == EffectType::DoT;
}

bool IsHealType(EffectType type)
{
  return type == EffectType::Heal
    || type == EffectType::HoT;
}

std::ostream& operator<<(std::ostream& out, const ModifierDomain& t)
{
  switch (t) {
  case ModifierDomain::Accuracy:
    return out << "accuracy";
    break;
  case ModifierDomain::Damage:
    return out << "damage";
    break;
  case ModifierDomain::Healing:
    return out << "healing";
    break;
  default:
    return out << "unknown";
    break;
  }
}

int VariableDamage::strength_() const
{
  return base_ + rng::DamageRoll(step_);
}
