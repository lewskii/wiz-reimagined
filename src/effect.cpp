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
  return type == EffectType::Heal;
}

std::ostream& operator<<(std::ostream& out, const CharmType& t)
{
  switch (t) {
  case CharmType::Accuracy:
    return out << "accuracy";
    break;
  case CharmType::Damage:
    return out << "damage";
    break;
  case CharmType::Heal:
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
