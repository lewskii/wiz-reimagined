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
    power_pips_{ 0 },
    active_{ true }
  {}

  Action SelectAction();

  void Cast(const Card& card, Wizard& target);

  void OverTimeTick();

  void AddPip();

  std::string name()      const { return stats.name; }
  School school()         const { return stats.school; }
  int max_health()        const { return stats.max_health; }
  int health()            const { return stats.health; }
  int pips()              const { return pips_; }
  int power_pips()        const { return power_pips_; }
  int total_pips()        const { return pips() + power_pips(); }
  int pips_for(School s)  const
  {
    return HasMastery(s)
      ? pips() + 2 * power_pips()
      : pips() + power_pips();
  }

  bool IsActive()         const { return active_; }

private:
  static const int kMaxPips = 7;

  void CastSuccess(const Card& card, Wizard& target);

  void ResolveCardEffects(
    const Card& card,
    Wizard& target,
    double damage_modifier,
    double heal_modifier
  );

  bool HasMastery(School s) const { return stats.school == s; }
  void UsePips(int n, School school);

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
  int power_pips_;
  bool active_;

  std::deque<std::shared_ptr<HangingOverTime>> over_time_effects;
  std::deque<std::shared_ptr<HangingCharm>> charms;

  WizardStats stats;
};
