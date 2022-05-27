#include <iostream>

#include "effect.hpp"
#include "rng.hpp"


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

std::ostream& operator<<(std::ostream& out, const HangingEffectDomain& t)
{
  switch (t) {
  case HangingEffectDomain::Accuracy:
    return out << "accuracy";
    break;
  case HangingEffectDomain::Damage:
    return out << "damage";
    break;
  case HangingEffectDomain::Heal:
    return out << "heal";
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
