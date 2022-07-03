

#include <iostream>

#include "battle.hpp"
#include "display.hpp"
#include "input.hpp"
#include "rng.hpp"


Battle::Battle(const Wizard& blue, const Wizard& red)
  : player_count{ 2 }
{
  auto order = rng::RandomOrder(blue, red);

  players_new.at(0).emplace(order.first);
  players_new.at(team_size).emplace(order.second);

  players.push_back(order.first);
  players.push_back(order.second);

  actions.reserve(player_count);
}

void Battle::Play()
{
  Winner winner = Winner::None;

  for (; winner == Winner::None; winner = CheckWinner())
  {
    RoundSetup();
    Display::Stats(players);

    SelectSpells();
    PlayActions();
  }

  if (winner == Winner::Blue)
    std::cout << '\n' << players[0].name() << " wins!\n";
  else if (winner == Winner::Red)
    std::cout << '\n' << players[1].name() << " wins!\n";
  else
    std::cout << '\n' << "draw!\n";
}


void Battle::RoundSetup()
{
  for (Wizard& w : players) {
    if (w.health() > 0)
      w.Activate();

    if (w.IsActive())
      w.AddPip();
  }
  actions.clear();
}

void Battle::SelectSpells()
{
  for (Wizard& w : players) {
    actions.push_back(Action(Input::SelectSpell(w)));
  }
}

void Battle::PlayActions()
{
  for (size_t i = 0; i < player_count; ++i) {
    std::cout << '\n';

    Wizard& w = players[i];

    w.OverTimeTick();

    if (w.IsActive()) {
      Action a = actions[i];
      if (a.IsSpell()) {
        Cast(w, a.card(), players[(i + 1) % player_count]);
      }
      else {
        Display::Pass(w);
      }
    }
  }
}



void Battle::Cast(Wizard& caster, const Card& card, Wizard& target)
{
  int accuracy_modifier
    = caster.UseAdditiveCharms(ModifierDomain::Accuracy, card.school);

  if (rng::PercentChance(card.accuracy + accuracy_modifier))
  {
    CastSuccess(caster, card, target);
  }
  else
  {
    Display::Fizzle(caster);
  }
}

void Battle::CastSuccess(Wizard& caster, const Card& card, Wizard& target)
{
  Display::Cast(caster, card);

  caster.UsePips(card.pip_cost, card.school);

  double damage_modifier = 1;
  double heal_modifier = 1;

  if (card.HasDamage())
    damage_modifier
    = caster.UseMultiplicativeCharms(ModifierDomain::Damage, card.school);
  if (card.HasHealing())
    heal_modifier
    = caster.UseMultiplicativeCharms(ModifierDomain::Healing, card.school);

  ResolveCardEffects(caster, card, target, damage_modifier, heal_modifier);
}

void Battle::ResolveCardEffects(
  Wizard& caster,
  const Card& card,
  Wizard& target,
  double damage_modifier,
  double heal_modifier
)
{
  for (auto& effect : card.effects) {
    switch (effect->type) {

    case Effect::Type::Damage: {
      if (target.IsActive()) {
        const auto damage = std::dynamic_pointer_cast<InstantEffect>(effect);
        target.TakeDamage(std::lround(damage->strength() * damage_modifier));
      }
      break;
    }

    case Effect::Type::DoT: {
      if (target.IsActive()) {
        const auto dot = std::dynamic_pointer_cast<DoT>(effect);
        const DoT modified_dot{
          std::lround(dot->strength * damage_modifier),
          dot->turns,
          dot->school,
          dot->target
        };
        target.AddOverTimeEffect(std::make_shared<HangingDoT>(modified_dot));
      }
      break;
    }

    case Effect::Type::Heal: {
      const auto heal = std::dynamic_pointer_cast<InstantEffect>(effect);
      caster.Heal(heal->strength());
      break;
    }

    case Effect::Type::HoT: {
      const auto hot = std::dynamic_pointer_cast<HoT>(effect);
      const HoT modified_hot{
        std::lround(hot->strength * heal_modifier),
        hot->turns,
        hot->target
      };
      caster.AddOverTimeEffect(std::make_shared<HangingHoT>(modified_hot));
      break;
    }

    case Effect::Type::Charm: {
      const auto charm = std::dynamic_pointer_cast<Charm>(effect);
      caster.charms.push_front(std::make_shared<HangingCharm>(*charm, card.name));
      break;
    }

    } // switch
  } // for
}



Battle::Winner Battle::CheckWinner() const
{
  int result = 0;
  if (!players.at(0).IsActive()) result += 1;
  if (!players.at(1).IsActive()) result += 2;
  auto test = static_cast<Winner>(result);
  return test;
}
