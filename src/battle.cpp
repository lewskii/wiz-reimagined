

#include <iostream>

#include "battle.hpp"

Battle::Battle(Wizard red, Wizard blue)
  : player_count{ 2 }
{
  if (rng::CoinToss())
  {
    players.push_back(blue);
    players.push_back(red);
  }
  else
  {
    players.push_back(red);
    players.push_back(blue);
  }

  actions.reserve(player_count);
}

void Battle::Play()
{

  while (players[0].health() > 0 && players[1].health() > 0)
  {
    RoundSetup();
    PrintStats();

    SelectActions();
    PlayActions();

    std::cin.ignore();
  }

  if (players[0].health() > 0)
    std::cout << players[0].name << " wins!\n";
  else
    std::cout << players[1].name << " wins!\n";
}


void Battle::RoundSetup()
{
  for (size_t i = 0; i < player_count; ++i) {
    Wizard& w = players[i];
    w.AddPip();
  }
  actions.clear();
}

void Battle::SelectActions()
{
  for (size_t i = 0; i < player_count; ++i) {
    actions.push_back(players[i].SelectAction());
  }
}

void Battle::PlayActions()
{
  for (size_t i = 0; i < player_count; ++i) {
    Wizard& w = players[i];
    if (w.health() > 0) {
      Action a = actions[i];
      if (a.IsSpell()) {
        Cast(w, a.card(), players[(i + 1) % player_count]);
      }
      else {
        std::cout << w.name << " passes.\n";
      }
    }
  }
}

void Battle::Cast(Wizard& caster, const Card& card, Wizard& target)
{
  if (rng::AccRoll(card.accuracy))
  {
    caster.UsePips(card.pip_cost);

    switch (card.effect.type) {
    case Effect::Type::Damage:
      target.DealDamage(card.effect.strength + rng::DamageRoll() * 10);
      break;
    case Effect::Type::Heal:
      caster.Heal(card.effect.strength);
      break;
    }

    std::cout << caster.name << " casts " << card.name << "!\n";

    if (target.health() == 0)
      std::cout << "\n" << target.name << " has been defeated!\n";
  }
  else
  {
    std::cout << caster.name << " fizzles!\n";
  }
}


void Battle::PrintStats()
{
  for (size_t i = 0; i < player_count; ++i) {
    Wizard w = players[i];
    std::cout << w.name << ": " << w.health() << " hp, " << w.pips() << " pip(s)\n";
  }
  std::cout << "\n";
}
