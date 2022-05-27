#pragma once

#include <vector>

#include "tools.hpp"
#include "wizard.hpp"


namespace display {

  void Stats(const std::vector<Wizard>& players);

  inline void Cast(const Wizard& w, const Card& card)
  {
    std::cout << w.name() << " casts " << card.name << "!\n";
  }
  inline void Fizzle(const Wizard& w)
  {
    std::cout << w.name() << " fizzles!\n";
  }
  inline void Pass(const Wizard& w)
  {
    std::cout << w.name() << " passes.\n";
  }

  inline void Damage(const Wizard& w, int damage)
  {
    std::cout << w.name() << " takes " << damage << " damage!\n";
  }
  inline void Healing(const Wizard& w, int heal)
  {
    std::cout << w.name() << " recovers " << heal << " hp!\n";
  }
  inline void Defeat(const Wizard& w)
  {
    std::cout << "\n" << w.name() << " has been defeated!\n";
  }
  inline void Revive(const Wizard& w)
  {
    std::cout << w.name() << " has been revived!\n";
  }

  inline void UsedCharmOrWard(const HangingEffect& effect)
  {
    std::cout << SignedNumString(effect.strength) << "% "
      << effect.domain << "\n";
  }

}