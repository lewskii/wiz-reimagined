#include <iostream>

#include "effect.hpp"
#include "rng.hpp"


bool SchoolsMatch(School a, School b)
{
    return a == School::Any
      || b == School::Any
      || a == b;
}

bool IsDamageType(Effect::Type type)
{
  return type == Effect::Type::Damage
    || type == Effect::Type::DoT;
}

bool IsHealType(Effect::Type type)
{
  return type == Effect::Type::Heal
    || type == Effect::Type::HoT;
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
