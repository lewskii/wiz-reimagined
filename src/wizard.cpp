#include <iostream>
#include <set>

#include "wizard.hpp"
#include "rng.hpp"
#include "display.hpp"

void Wizard::Cast(const Card& card, Wizard& target)
{
  int accuracy_modifier
    = UseAdditiveCharms(HangingEffectDomain::Accuracy, card.school);

  if (rng::PercentChance(card.accuracy + accuracy_modifier))
  {
    CastSuccess(card, target);
  }
  else
  {
    display::Fizzle(*this);
  }
}

void Wizard::CastSuccess(const Card& card, Wizard& target)
{
  display::Cast(*this, card);

  UsePips(card.pip_cost, card.school);

  double damage_modifier = 1;
  double heal_modifier = 1;

  if (card.HasDamage())
    damage_modifier
    = UseMultiplicativeCharms(HangingEffectDomain::Damage, card.school);
  if (card.HasHealing())
    heal_modifier
    = UseMultiplicativeCharms(HangingEffectDomain::Healing, card.school);

  ResolveCardEffects(card, target, damage_modifier, heal_modifier);
}

void Wizard::ResolveCardEffects(
  const Card& card,
  Wizard& target,
  double damage_modifier,
  double heal_modifier
)
{
  for (auto i = card.effects.begin(); i < card.effects.end(); ++i) {
    Card::EffectPtr effect = *i;

    switch (effect->type) {

    case EffectType::Damage: {
      if (target.IsActive()) {
        const auto damage = std::dynamic_pointer_cast<InstantEffect>(effect);
        target.TakeDamage(std::lround(damage->strength() * damage_modifier));
      }
      break;
    }

    case EffectType::DoT: {
      if (target.IsActive()) {
        const auto dot = std::dynamic_pointer_cast<DoT>(effect);
        const DoT modified_dot{
          std::lround(dot->strength * damage_modifier),
          dot->turns,
          dot->school
        };
        target.AddOverTimeEffect(std::make_shared<HangingDoT>(modified_dot));
      }
      break;
    }

    case EffectType::Heal: {
      const auto heal = std::dynamic_pointer_cast<InstantEffect>(effect);
      Heal(heal->strength());
      break;
    }

    case EffectType::HoT: {
      const auto hot = std::dynamic_pointer_cast<HoT>(effect);
      const HoT modified_hot{
        std::lround(hot->strength * heal_modifier),
        hot->turns
      };
      AddOverTimeEffect(std::make_shared<HangingHoT>(modified_hot));
      break;
    }

    case EffectType::Charm: {
      const auto charm = std::dynamic_pointer_cast<Charm>(effect);
      charms.push_front(std::make_shared<HangingCharm>(*charm, card.name));
      break;
    }

    } // switch
  } // for
}

void Wizard::UsePips(int n, School school)
{
  int remaining_cost = n;

  if (HasMastery(school)) {
    int max_used_power_pips = remaining_cost / 2;
    int used_power_pips = std::min(max_used_power_pips, power_pips());
    power_pips_ -= used_power_pips;
    remaining_cost -= used_power_pips * 2;
  }

  int used_pips = std::min(remaining_cost, pips());
  pips_ -= used_pips;
  remaining_cost -= used_pips;

  int used_power_pips = std::min(remaining_cost, power_pips());
  power_pips_ -= used_power_pips;
}


static int AdditiveFold(int fold, int next)
{
  return fold + next;
}

static double MultiplicativeFold(double fold, int next)
{
  return fold * (next / 100.0 + 1.0);
}

template <typename T>
T Wizard::UseCharms(
  HangingEffectDomain type,
  School school,
  T (*NextFold)(T, int)
)
{
  std::set<std::string> used_ids;
  T fold = 1;

  auto i = charms.begin();

  while (i < charms.end()) {
    auto& charm = *i;
    if (charm->domain == type
      && charm->school == school
      && used_ids.insert(charm->id).second
      ) {
      fold = NextFold(fold, charm->strength);
      display::UsedCharmOrWard(*charm);
      i = charms.erase(i);
    }
    else {
      ++i;
    }
  }

  return fold;
}

double Wizard::UseMultiplicativeCharms(HangingEffectDomain type, School school)
{
  return UseCharms(type, school, &MultiplicativeFold);
}

int Wizard::UseAdditiveCharms(HangingEffectDomain type, School school)
{
  return UseCharms(type, school, &AdditiveFold);
}

void Wizard::OverTimeTick()
{
  auto i = over_time_effects.begin();
  while (i < over_time_effects.end()) {
    auto effect = *i;

    switch (effect->type) {
    case EffectType::DoT:
      TakeDamage(effect->per_turn);
      break;
    case EffectType::HoT:
      Heal(effect->per_turn);
      break;
    }

    if (!IsActive())
      break;

    --(effect->turns_left);
    if (effect->turns_left <= 0)
      i = over_time_effects.erase(i);
    else
      ++i;
  }
}

void Wizard::AddPip()
{
  if (total_pips() < kMaxPips) {
    if (rng::PercentChance(stats.pip_chance))
      ++power_pips_;
    else
      ++pips_;
  }
}

int Wizard::TakeDamage(int damage) {
  display::Damage(*this, damage);
  stats.health = std::max(0, health() - damage);

  if (health() == 0) {
    Die();
  }

  return damage;
}

void Wizard::Die()
{
  display::Defeat(*this);
  active_ = false;
  pips_ = 0;
  over_time_effects.clear();
  charms.clear();
}

int Wizard::Heal(int strength) {
  display::Healing(*this, strength);

  if (health() == 0) {
    Revive();
  }

  stats.health = std::min(max_health(), health() + strength);
  return strength;
}

void Wizard::Revive()
{
  display::Revive(*this);
  active_ = true;
}

void Wizard::AddOverTimeEffect(std::shared_ptr<HangingOverTime> effect)
{
  over_time_effects.push_front(effect);
}
