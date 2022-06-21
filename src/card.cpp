

#include "card.hpp"

bool Card::HasDamage() const
{
  for (auto& effect : effects) {
    if (IsDamageType(effect->type))
      return true;
  }
  return false;
}

bool Card::HasHealing() const
{
  for (auto& effect : effects) {
    if (IsHealType(effect->type))
      return true;
  }
  return false;
}

bool Card::HasTarget(std::initializer_list<EffectPtr> effects, Target target)
{
  for (auto& effect : effects) {
    if (effect->target == target) return true;
  }
  return false;
}
