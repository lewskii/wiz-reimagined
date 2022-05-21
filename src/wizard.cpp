#include <iostream>

#include "wizard.hpp"
#include "rng.hpp"

Action Wizard::SelectAction()
{
  char c;
  std::cout << "select card for " << name << ": ";
  std::cin >> c;
  if (isdigit(c) && c - '0' < deck.size())
    return Action(deck[c - '0']);
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
      target.DealDamage(card.effects[0]->strength());
      break;
    case Effect::Type::Heal:
      Heal(card.effects[0]->strength());
      break;
    case Effect::Type::DoT:
      auto dot = std::dynamic_pointer_cast<Effect::DoT>(e);
      std::cout << "this should do " << dot->damage_
        << " over " << dot->turns_ << " turns\n";
      break;
    }

    std::cout << name << " casts " << card.name << "!\n";

    if (target.health() == 0)
      std::cout << "\n" << target.name << " has been defeated!\n";
  }
  else
  {
    std::cout << name << " fizzles!\n";
  }
}
