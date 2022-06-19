#include <iostream>

#include "display.hpp"


void display::Stats(const std::vector<Wizard>& players)
{
  std::cout << '\n';
  for (size_t i = 0; i < players.size(); ++i) {
    Wizard w = players[i];
    std::cout << w.name() << ": "
      << w.health() << " hp, "
      << w.pips() << " pip(s)";

    if (w.power_pips() > 0)
      std::cout << ", " << w.power_pips() << " power pip(s)";

    std::cout << '\n';
  }
  std::cout << "\n";
}
