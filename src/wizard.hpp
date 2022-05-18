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

  Card& SelectSpell() {
    if (deck.size() > 1 && pips > 1) {
      return deck[1];
    }
    else {
      return deck[0];
    }
  }

  const std::string name;
  int health;
  int pips = 0;

  std::vector<Card> deck;
};

