#pragma once

#include <vector>

#include "tools.hpp"
#include "wizard.hpp"


namespace display {

  void PrintStats(const std::vector<Wizard>& players);

  static void PrintCast(const Wizard& w, const Card& card)
  {
    std::cout << w.name() << " casts " << card.name << "!\n";
  }
  static void PrintFizzle(const Wizard& w)
  {
    std::cout << w.name() << " fizzles!\n";
  }
  static void PrintPass(const Wizard& w)
  {
    std::cout << w.name() << " passes.\n";
  }

  static void PrintDamage(const Wizard& w, int damage)
  {
    std::cout << w.name() << " takes " << damage << " damage!\n";
  }
  static void PrintHealing(const Wizard& w, int heal)
  {
    std::cout << w.name() << " recovers " << heal << " hp!\n";
  }
  static void PrintDefeat(const Wizard& w)
  {
    std::cout << "\n" << w.name() << " has been defeated!\n";
  }

  static void PrintUsedCharmOrWard(const HangingEffect& effect)
  {
    std::cout << SignedNumString(effect.strength) << "%\n";
  }

}