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
    std::cout << stats.name << " casts " << card.name << "!\n";

    UsePips(card.pip_cost);

    for (auto i = card.effects.begin(); i < card.effects.end(); ++i) {
      Card::EffectPtr effect = *i;
      switch (effect->type) {
      case Effect::Type::Damage:
        target.TakeDamage(effect->strength());
        break;
      case Effect::Type::Heal:
        Heal(card.effects[0]->strength());
        break;
      case Effect::Type::DoT:
        auto dot = std::dynamic_pointer_cast<Effect::DoT>(effect);
        target.AddOverTimeEffect(std::make_shared<HangingEffect::DoT>(*dot));
        break;
      }
    }

    if (target.health() == 0)
      std::cout << "\n" << target.name() << " has been defeated!\n";
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
    case Effect::Type::DoT:
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
  stats.health = std::max(0, stats.health - damage);
  return damage;
}

inline int Wizard::Heal(int strength) {
  std::cout << name() << " heals " << strength << " hp!\n";
  stats.health = std::min(stats.max_health, stats.health + strength);
  return strength;
}

void Wizard::AddOverTimeEffect(std::shared_ptr<HangingEffect::OverTime> effect)
{
  over_time_effects.push_back(effect);
}
