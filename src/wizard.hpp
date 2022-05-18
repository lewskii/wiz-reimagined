#pragma once

#include <vector>

#include "action.hpp"
#include "card.hpp"


class Wizard {
public:
  Wizard(const std::string name, const int hp)
    :
    name{ name },
    health_{ hp }
  {}

  int DealDamage(int damage) {
    health_ = std::max(0, health_ - damage);
    return damage;
  }

  int health() { return health_; }

  int pips() { return pips_; }

  void AddPip() {
    pips_ = std::min(pips_ + 1, kMaxPips);
  }

  void UsePips(int n) {
    pips_ = std::max(0, pips_ - n);
  }

  void AddSpell(Card c) {
    deck.push_back(c);
  }

  Action SelectAction() {
    if (deck.size() > 1 && pips_ > 1) {
      return deck[1];
    }
    else {
      return deck[0];
    }
  }

  const std::string name;

private:
  static const int kMaxPips = 7;

  int health_;
  int pips_ = 0;

  std::vector<Card> deck;
};

