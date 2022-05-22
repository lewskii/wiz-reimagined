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
  if (rng::AccRoll(card.accuracy))
  {
    UsePips(card.pip_cost);

    Card::EffectPtr e = card.effects[0];
    switch (e->type) {
    case Effect::Type::Damage:
      target.TakeDamage(card.effects[0]->strength());
      break;
    case Effect::Type::Heal:
      Heal(card.effects[0]->strength());
      break;
    case Effect::Type::DoT:
      auto dot = std::dynamic_pointer_cast<Effect::DoT>(e);
      target.over_time_effects.push_back(std::make_shared<Effect::HangingDoT>(*dot));
      break;
    }

    std::cout << stats.name << " casts " << card.name << "!\n";

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
  RemoveEndedOverTimes();

  for (auto i = over_time_effects.begin(); i < over_time_effects.end(); ++i) {
    auto effect = i->get();
    --(effect->turns_left);

    switch (effect->type) {
    case Effect::Type::DoT:
      TakeDamage(effect->per_turn);
      break;
    }
  }
}

inline int Wizard::TakeDamage(int damage) {
  std::cout << name() << " took " << damage << " damage!\n";
  stats.health = std::max(0, stats.health - damage);
  return damage;
}

inline int Wizard::Heal(int strength) {
  std::cout << name() << " was healed for " << strength << "!\n";
  stats.health = std::min(stats.max_health, stats.health + strength);
  return strength;
}

void Wizard::RemoveEndedOverTimes()
{
  auto iter = over_time_effects.begin();
  while (iter < over_time_effects.end()) {
    if (iter->get()->turns_left <= 0)
      iter = over_time_effects.erase(iter);
    else
      ++iter;
  }
}
