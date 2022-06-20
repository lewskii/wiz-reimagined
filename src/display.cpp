#include <iostream>

#include "display.hpp"
#include "tools.hpp"

static void PrintPips(int n, bool power = false)
{
  std::string label = power ? " power pip" : " pip";
  if (n > 1 || n == 0)
    label += 's';
  std::cout << ", " << n << label;
}


void Display::Stats(const std::vector<Wizard>& players)
{
  std::cout << '\n';
  for (auto& w : players) {
    std::cout << w.name() << ": " << w.health() << " hp";

    if (w.pips() > 0 || w.power_pips() == 0)
      PrintPips(w.pips());

    if (w.power_pips() > 0)
      PrintPips(w.power_pips(), true);

    std::cout << '\n';
  }
  std::cout << "\n";
}

void Display::UsedCharmOrWard(const HangingEffect& effect)
{
    std::cout << SignedNumString(effect.strength) << "% "
        << effect.domain << "\n";
}
