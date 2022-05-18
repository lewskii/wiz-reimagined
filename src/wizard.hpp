#pragma once

#include <vector>

#include "card.hpp"


class Wizard {
public:
  static const int max_pips = 7;

  Wizard(const std::string name, const int hp)
    :
    name{ name },
    health{ hp }
  {}

  int DealDamage(int damage) {
    int dealt = std::min(damage, health);
    health -= dealt;
    return dealt;
  }

  const std::string name;
  int health;
  int pips = 0;

  std::vector<Card> deck;
};

