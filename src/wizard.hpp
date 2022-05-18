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
    health = std::max(0, health - damage);
    return damage;
  }

  const std::string name;
  int health;
  int pips = 0;

  std::vector<Card> deck;
};

