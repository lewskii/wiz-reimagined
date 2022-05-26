#include <iostream>

#include "display.hpp"


void display::PrintStats(const std::vector<Wizard>& players)
{
  std::cout << '\n';
  for (size_t i = 0; i < players.size(); ++i) {
    Wizard w = players[i];
    std::cout << w.name() << ": "
      << w.health() << " hp, "
      << w.pips() << " pip(s)"
      << '\n';
  }
  std::cout << "\n";
}
