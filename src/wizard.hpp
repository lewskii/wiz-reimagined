#pragma once

#include <vector>

#include "action.hpp"
#include "card.hpp"


class Wizard {
public:
  Wizard(const std::string name, const int hp)
    :
    name{ name },
    max_health_{ hp },
    health_{ hp }
  {}

  void Cast(const Card& card, Wizard& target);

  int DealDamage(int damage) {
    health_ = std::max(0, health_ - damage);
    return damage;
  }

  int Heal(int strength) {
    health_ = std::min(max_health_, health_ + strength);
    return strength;
  }

  int max_health() const { return max_health_; }

  int health() const { return health_; }

  int pips() const { return pips_; }

  void AddPip() {
    pips_ = std::min(pips_ + 1, kMaxPips);
  }

  void UsePips(int n) {
    pips_ = std::max(0, pips_ - n);
  }

  void AddSpell(const Card& c) {
    deck.push_back(c);
  }

  Action SelectAction();

  const std::string name;

private:
  static const int kMaxPips = 7;

  int max_health_;
  int health_;
  int pips_ = 0;

  std::vector<Card> deck;
};

