

#include <iostream>

#include "battle.hpp"

void Battle::Play()
{
  while (players[0].health > 0 && players[1].health > 0) {
    for (size_t i = 0; i < player_count; ++i) {
      Wizard w = players[i];
      std::cout << w.name << "'s hp: " << w.health << "\n";
    }

    for (size_t i = 0; i < player_count; ++i) {
      Wizard w = players[i];
      if (w.health > 0) {
        Cast(w.deck[0], players[(i + 1) % player_count]);
      }
    }

    std::cin.ignore();
  }

  if (players[0].health > 0)
    std::cout << players[0].name << " wins!\n";
  else
    std::cout << players[1].name << " wins!\n";
}
