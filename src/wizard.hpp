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

  void OverTimeTick();

  int TakeDamage(int damage);

  int Heal(int strength);

  void AddPip() { pips_ = std::min(pips_ + 1, kMaxPips); }

  void UsePips(int n) { pips_ = std::max(0, pips_ - n); }

  int max_health() const { return stats.max_health; }

  int health() const { return stats.health; }

  int pips() const { return pips_; }

  std::string name() { return stats.name; };

  std::vector<std::shared_ptr<Effect::HangingOverTime>> over_time_effects;

private:
  static const int kMaxPips = 7;

  void RemoveEndedOverTimes();

  int pips_;

  WizardStats stats;
};

