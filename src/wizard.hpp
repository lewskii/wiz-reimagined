#pragma once

#include <deque>

#include "wizardstats.hpp"



class Wizard {
public:
  Wizard(const WizardStats& stats)
    :
    stats{ stats },
    pips_{ 0 },
    power_pips_{ 0 },
    active_{ false }
  {}

  friend class Battle;
  friend class Input;

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
  
  void Activate() { active_ = true; }

private:
  static const int kMaxPips = 7;


  bool HasMastery(School s) const { return stats.school == s; }
  void UsePips(int n, School school);

  template <typename T>
  T UseCharms(ModifierDomain type, School school, T(*NextFold)(T, int));
  int UseAdditiveCharms(ModifierDomain type, School school);
  double UseMultiplicativeCharms(ModifierDomain type, School school);

  void ResolveIncomingEffect(
    const Card::EffectPtr& effect,
    double modifier,
    std::string id
  );

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
