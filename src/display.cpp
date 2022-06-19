#include <iostream>

#include "display.hpp"

static void PrintPips(int n, bool power = false)
{
  std::string label = power ? " power pip" : " pip";
  if (n > 1 || n == 0)
    label += 's';
  std::cout << ", " << n << label;
}


void display::Stats(const std::vector<Wizard>& players)
{
  std::cout << '\n';
  for (size_t i = 0; i < players.size(); ++i) {
    Wizard w = players[i];
    std::cout << w.name() << ": " << w.health() << " hp";

    if (w.pips() > 0 || w.power_pips() == 0)
      PrintPips(w.pips());

    if (w.power_pips() > 0)
      PrintPips(w.power_pips(), true);

    std::cout << '\n';
  }
  std::cout << "\n";
}
