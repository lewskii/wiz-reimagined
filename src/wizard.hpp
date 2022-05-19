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

  void Cast(const Card card, Wizard& target)
  {
    if (rng::AccRoll(card.accuracy))
    {
      UsePips(card.pip_cost);

      switch (card.effect.type) {
      case Effect::Type::Damage:
        target.DealDamage(card.effect.strength + rng::DamageRoll() * 10);
        break;
      case Effect::Type::Heal:
        Heal(card.effect.strength);
        break;
      }

      std::cout << name << " casts " << card.name << "!\n";

      if (target.health() == 0)
        std::cout << "\n" << target.name << " has been defeated!\n";
    }
    else
    {
      std::cout << name << " fizzles!\n";
    }
  }

  int DealDamage(int damage) {
    health_ = std::max(0, health_ - damage);
    return damage;
  }

  int Heal(int strength) {
    health_ = std::min(max_health_, health_ + strength);
    return strength;
  }

  int max_health() { return max_health_; }

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
    char c;
    std::cout << "select card for " << name << ": ";
    std::cin >> c;
    if (isdigit(c) && c - '0' < deck.size())
      return Action(deck[c - '0']);
    else
      return Pass::pass;
  }

  const std::string name;

private:
  static const int kMaxPips = 7;

  int max_health_;
  int health_;
  int pips_ = 0;

  std::vector<Card> deck;
};

