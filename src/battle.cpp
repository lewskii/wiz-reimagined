

#include <iostream>

#include "battle.hpp"

void Battle::Play()
{
  PrintStats();

  while (players[0].health > 0 && players[1].health > 0)
  {
    RoundSetup();

    for (size_t i = 0; i < player_count; ++i) {
      Wizard w = players[i];
      if (w.health > 0) {
        Cast(w.deck[0], players[(i + 1) % player_count]);
      }
    }

    PrintStats();

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
    Wizard w = players[i];
    w.pips = std::min(w.pips + 1, 7);
  }
}

void Battle::Cast(const Card card, Wizard& target)
{
  if (rng::AccRoll() <= card.accuracy)
  {
    int damage = target.DealDamage(card.damage + rng::DamageRoll() * 10);
    std::cout << target.name << " took " << damage << " damage from " << card.name << "!\n";
    if (target.health == 0)
      std::cout << "\n" << target.name << " has been defeated!\n\n";
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
    std::cout << w.name << ": " << w.health << " hp\n";
  }
  std::cout << "\n";
}
