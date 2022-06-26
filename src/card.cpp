

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

Card::Target Card::RequiredTarget(std::initializer_list<EffectPtr> effects)
{
  for (auto& e : effects) {
    if (e->target == Effect::Target::Enemy)
      return Card::Target::Enemy;
    if (e->target == Effect::Target::Ally)
      return Card::Target::Ally;
  }

  return Target::None;
}
