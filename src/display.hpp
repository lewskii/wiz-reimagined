#pragma once

#include <vector>

#include "tools.hpp"
#include "wizard.hpp"


namespace display {

  void Stats(const std::vector<Wizard>& players);

  static void Cast(const Wizard& w, const Card& card)
  {
    std::cout << w.name() << " casts " << card.name << "!\n";
  }
  static void Fizzle(const Wizard& w)
  {
    std::cout << w.name() << " fizzles!\n";
  }
  static void Pass(const Wizard& w)
  {
    std::cout << w.name() << " passes.\n";
  }

  static void Damage(const Wizard& w, int damage)
  {
    std::cout << w.name() << " takes " << damage << " damage!\n";
  }
  static void Healing(const Wizard& w, int heal)
  {
    std::cout << w.name() << " recovers " << heal << " hp!\n";
  }
  static void Defeat(const Wizard& w)
  {
    std::cout << "\n" << w.name() << " has been defeated!\n";
  }
  static void Revive(const Wizard& w)
  {
    std::cout << w.name() << " has been revived!\n";
  }

  static void UsedCharmOrWard(const HangingEffect& effect)
  {
    std::cout << SignedNumString(effect.strength) << "% "
      << effect.domain << "\n";
  }

}