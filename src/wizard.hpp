#pragma once

#include <vector>

#include "action.hpp"
#include "wizardstats.hpp"


class Wizard {
public:
  Wizard(const WizardStats& stats)
    :
    stats{ stats },
    pips_{ 0 },
    active_{ true }
  {}

  Action SelectAction();

  void Cast(const Card& card, Wizard& target);

  void OverTimeTick();

  void AddPip() { pips_ = std::min(pips_ + 1, kMaxPips); }

  int max_health() const { return stats.max_health; }
  int health() const { return stats.health; }
  int pips() const { return pips_; }
  std::string name() const { return stats.name; };

  bool IsActive() const { return active_; }

private:
  static const int kMaxPips = 7;

  void AddOverTimeEffect(std::shared_ptr<HangingEffect::OverTime> effect);

  void UsePips(int n) { pips_ = std::max(0, pips_ - n); }

  int TakeDamage(int damage);
  int Heal(int strength);

  int pips_;
  bool active_;

  std::vector<std::shared_ptr<HangingEffect::OverTime>> over_time_effects;

  WizardStats stats;
};

