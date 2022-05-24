#include <iostream>

#include "wizard.hpp"
#include "rng.hpp"

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
  if (rng::PercentChance(card.accuracy))
  {
    std::cout << name() << " casts " << card.name << "!\n";

    UsePips(card.pip_cost);

    for (auto i = card.effects.begin(); i < card.effects.end(); ++i) {
      Card::EffectPtr effect = *i;
      switch (effect->type) {
      case EffectType::Damage: {
        if (target.IsActive()) {
          const auto damage = std::dynamic_pointer_cast<InstantEffect>(effect);
          target.TakeDamage(damage->strength());
        }
        break;
      }
      case EffectType::Heal: {
        const auto heal = std::dynamic_pointer_cast<InstantEffect>(effect);
        Heal(heal->strength());
        break;
      }
      case EffectType::DoT: {
        if (target.IsActive()) {
          const auto dot = std::dynamic_pointer_cast<DoT>(effect);
          target.AddOverTimeEffect(std::make_shared<HangingDoT>(*dot));
        }
        break;
      }
      }
    }
  }
  else
  {
    std::cout << stats.name << " fizzles!\n";
  }
}

void Wizard::OverTimeTick()
{
  auto i = over_time_effects.begin();
  while (i < over_time_effects.end()) {
    auto effect = i->get();

    switch (effect->type) {
    case EffectType::DoT:
      TakeDamage(effect->per_turn);
      break;
    }

    --(effect->turns_left);
    if (effect->turns_left <= 0)
      i = over_time_effects.erase(i);
    else
      ++i;
  }
}

inline int Wizard::TakeDamage(int damage) {
  std::cout << name() << " takes " << damage << " damage!\n";
  stats.health = std::max(0, health() - damage);

  if (health() == 0) {
    active_ = false;
    std::cout << "\n" << name() << " has been defeated!\n";
  }

  return damage;
}

inline int Wizard::Heal(int strength) {
  std::cout << name() << " heals " << strength << " hp!\n";
  stats.health = std::min(max_health(), health() + strength);
  return strength;
}

void Wizard::AddOverTimeEffect(std::shared_ptr<HangingOverTime> effect)
{
  over_time_effects.push_back(effect);
}
