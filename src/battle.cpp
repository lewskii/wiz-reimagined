

#include <iostream>

#include "battle.hpp"

void Battle::Play()
{

  while (players[0].health > 0 && players[1].health > 0)
  {
    RoundSetup();
    PrintStats();

    for (size_t i = 0; i < player_count; ++i) {
      Wizard& w = players[i];
      if (w.health > 0) {
        Cast(w, w.deck[0], players[(i + 1) % player_count]);
      }
    }

    std::cin.ignore();
  }

  if (players[0].health > 0)
    std::cout << players[0].name << " wins!\n";
  else
    std::cout << players[1].name << " wins!\n";
}


void Battle::RoundSetup()
{
  for (size_t i = 0; i < player_count; ++i) {
    Wizard& w = players[i];
    w.pips = std::min(w.pips + 1, kMaxPips);
  }
}

void Battle::Cast(Wizard& caster, const Card& card, Wizard& target)
{
  if (rng::AccRoll() <= card.accuracy)
  {
    caster.pips -= card.pip_cost;
    target.DealDamage(card.damage + rng::DamageRoll() * 10);

    std::cout << target.name << " took " << card.damage << " damage from " << card.name << "!\n";
    if (target.health == 0)
      std::cout << "\n" << target.name << " has been defeated!\n";
  }
  else
  {
    std::cout << card.name << " fizzled!\n";
  }
}


void Battle::PrintStats()
{
  for (size_t i = 0; i < player_count; ++i) {
    Wizard w = players[i];
    std::cout << w.name << ": " << w.health << " hp, " << w.pips << " pip(s)\n";
  }
  std::cout << "\n";
}
