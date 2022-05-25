

#include "card.hpp"

bool Card::HasDamage() const
{
  for (auto i = effects.begin(); i < effects.end(); ++i) {
    if (IsDamageType((*i)->type))
      return true;
  }
  return false;
}

bool Card::HasHealing() const
{
  for (auto i = effects.begin(); i < effects.end(); ++i) {
    if (IsHealType((*i)->type))
      return true;
  }
  return false;
}
