

#include <iostream>

#include "battle.hpp"
#include "display.hpp"
#include "input.hpp"

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
    display::Stats(players);

    SelectActions();
    PlayActions();
  }

  if (players[0].health() > 0)
    std::cout << '\n' << players[0].name() << " wins!\n";
  else
    std::cout << '\n' << players[1].name() << " wins!\n";
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
    actions.push_back(Input::SelectAction(players[i]));
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
        w.Cast(a.card(), players[(i + 1) % player_count]);
      }
      else {
        display::Pass(w);
      }
    }
  }
}