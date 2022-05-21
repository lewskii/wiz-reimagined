#pragma once

#include <vector>

#include "action.hpp"
#include "wizardstats.hpp"


class Wizard {
public:
  Wizard(const WizardStats& stats)
    :
    stats{ stats },
    pips_{ 0 }
  {}

  Action SelectAction();

  void Cast(const Card& card, Wizard& target);

  int TakeDamage(int damage) {
    stats.health = std::max(0, stats.health - damage);
    return damage;
  }

  int Heal(int strength) {
    stats.health = std::min(stats.max_health, stats.health + strength);
    return strength;
  }

  void AddPip() { pips_ = std::min(pips_ + 1, kMaxPips); }

  void UsePips(int n) { pips_ = std::max(0, pips_ - n); }

  int max_health() const { return stats.max_health; }

  int health() const { return stats.health; }

  int pips() const { return pips_; }

  std::string name() { return stats.name; };

private:
  static const int kMaxPips = 7;

  int pips_;

  WizardStats stats;
};

