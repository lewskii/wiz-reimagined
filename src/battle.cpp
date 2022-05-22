

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
    std::cout << players[0].name() << " wins!\n";
  else
    std::cout << players[1].name() << " wins!\n";
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

    w.OverTimeTick();
    if (w.health() == 0) {
      std::cout << "\n" << w.name() << " has been defeated!\n";
    }

    if (w.health() > 0) {
      Action a = actions[i];
      if (a.IsSpell()) {
        w.Cast(a.card(), players[(i + 1) % player_count]);
      }
      else {
        std::cout << w.name() << " passes.\n";
      }
    }
  }
}


void Battle::PrintStats() const
{
  for (size_t i = 0; i < player_count; ++i) {
    Wizard w = players[i];
    std::cout << w.name() << ": " << w.health() << " hp, " << w.pips() << " pip(s)\n";
  }
  std::cout << "\n";
}
