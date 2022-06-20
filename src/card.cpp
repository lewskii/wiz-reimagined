

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

TargetSelection Card::DetermineTarget(std::initializer_list<EffectPtr> effects)
{
  for (auto& effect : effects) {
    if (effect->target == Target::Ally) return TargetSelection::Ally;
    if (effect->target == Target::Enemy) return TargetSelection::Enemy;
  }
  return TargetSelection::None;
}
