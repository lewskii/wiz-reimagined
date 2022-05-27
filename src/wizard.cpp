#include <iostream>

#include "wizard.hpp"
#include "rng.hpp"
#include "display.hpp"

Action Wizard::SelectAction()
{
  char c;
  std::cout << "select card for " << name() << ": ";
  std::cin >> c;
  if (isdigit(c) && c - '0' < stats.deck.size())
    return Action(stats.deck[c - '0']);
  else
    return Pass::pass;
}

void Wizard::Cast(const Card& card, Wizard& target)
{
  int accuracy_modifier = UseAdditiveCharms(CharmType::Accuracy);

  if (rng::PercentChance(card.accuracy + accuracy_modifier))
  {
    display::Cast(*this, card);

    UsePips(card.pip_cost);

    double damage_modifier = 1;
    double heal_modifier = 1;
    
    if (card.HasDamage())
      damage_modifier = UseMultiplicativeCharms(CharmType::Damage);
    if (card.HasHealing())
      heal_modifier = UseMultiplicativeCharms(CharmType::Heal);

    for (auto i = card.effects.begin(); i < card.effects.end(); ++i) {
      Card::EffectPtr effect = *i;

      switch (effect->type) {

      case EffectType::Damage: {
        if (target.IsActive()) {
          const auto damage = std::dynamic_pointer_cast<InstantEffect>(effect);
          target.TakeDamage(std::lround(damage->strength() * damage_modifier));
        }
        break;
      }

      case EffectType::DoT: {
        if (target.IsActive()) {
          const auto dot = std::dynamic_pointer_cast<DoT>(effect);
          const DoT modified_dot{
            std::lround(dot->strength * damage_modifier),
            dot->turns
          };
          target.AddOverTimeEffect(std::make_shared<HangingDoT>(modified_dot));
        }
        break;
      }

      case EffectType::Heal: {
        const auto heal = std::dynamic_pointer_cast<InstantEffect>(effect);
        Heal(heal->strength());
        break;
      }

      case EffectType::HoT: {
        const auto hot = std::dynamic_pointer_cast<HoT>(effect);
        const HoT modified_hot{
          std::lround(hot->strength * heal_modifier),
          hot->turns
        };
        AddOverTimeEffect(std::make_shared<HangingHoT>(modified_hot));
        break;
      }
      
      case EffectType::Charm: {
        const auto charm = std::dynamic_pointer_cast<Charm>(effect);
        charms.push_back(std::make_shared<HangingCharm>(*charm));
        break;
      }

      } // switch
    } // for
  }
  else
  {
    display::Fizzle(*this);
  }
}

double Wizard::UseMultiplicativeCharms(CharmType type)
{
  double fold = 1;

  auto i = charms.begin();

  while (i < charms.end()) {
    auto &charm = *i;
    if (charm->type == type) {
      fold *= charm->strength / 100.0 + 1.0;
      display::UsedCharmOrWard(*charm);
      i = charms.erase(i);
    }
    else {
      ++i;
    }
  }

  return fold;
}

int Wizard::UseAdditiveCharms(CharmType type)
{
  int fold = 0;

  auto i = charms.begin();

  while (i < charms.end()) {
    auto &charm = *i;
    if (charm->type == type) {
      fold += charm->strength;
      display::UsedCharmOrWard(*charm);
      i = charms.erase(i);
    }
    else {
      ++i;
    }
  }

  return fold;
}

void Wizard::OverTimeTick()
{
  auto i = over_time_effects.begin();
  while (i < over_time_effects.end()) {
    auto effect = *i;

    switch (effect->type) {
    case EffectType::DoT:
      TakeDamage(effect->per_turn);
      break;
    case EffectType::HoT:
      Heal(effect->per_turn);
      break;
    }

    if (!IsActive())
      break;

    --(effect->turns_left);
    if (effect->turns_left <= 0)
      i = over_time_effects.erase(i);
    else
      ++i;
  }
}

inline int Wizard::TakeDamage(int damage) {
  display::Damage(*this, damage);
  stats.health = std::max(0, health() - damage);

  if (health() == 0) {
    Die();
  }

  return damage;
}

inline void Wizard::Die()
{
  display::Defeat(*this);
  active_ = false;
  pips_ = 0;
  over_time_effects.clear();
  charms.clear();
}

inline int Wizard::Heal(int strength) {
  display::Healing(*this, strength);

  if (health() == 0) {
    Revive();
  }

  stats.health = std::min(max_health(), health() + strength);
  return strength;
}

void Wizard::Revive()
{
  display::Revive(*this);
  active_ = true;
}

void Wizard::AddOverTimeEffect(std::shared_ptr<HangingOverTime> effect)
{
  over_time_effects.push_back(effect);
}
