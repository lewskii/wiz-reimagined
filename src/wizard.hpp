#pragma once

#include <deque>

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

  void AddPip() { pips_ = std::min(pips() + 1, kMaxPips); }

  int max_health() const { return stats.max_health; }
  int health() const { return stats.health; }
  int pips() const { return pips_; }
  std::string name() const { return stats.name; };

  bool IsActive() const { return active_; }

private:
  static const int kMaxPips = 7;

  void CastSuccess(const Card& card, Wizard& target);

  void ResolveCardEffects(
    const Card& card,
    Wizard& target,
    double damage_modifier,
    double heal_modifier
  );

  void UsePips(int n) { pips_ = std::max(0, pips() - n); }

  template <typename T>
  T UseCharms(HangingEffectDomain type, School school, T(*NextFold)(T, int));
  int UseAdditiveCharms(HangingEffectDomain type, School school);
  double UseMultiplicativeCharms(HangingEffectDomain type, School school);

  void AddOverTimeEffect(std::shared_ptr<HangingOverTime> effect);

  int TakeDamage(int damage);
  void Die();
  int Heal(int strength);
  void Revive();

  int pips_;
  bool active_;

  std::deque<std::shared_ptr<HangingOverTime>> over_time_effects;
  std::deque<std::shared_ptr<HangingCharm>> charms;

  WizardStats stats;
};
