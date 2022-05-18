#pragma once

#include <vector>

#include "card.hpp"


class Wizard {
public:
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

