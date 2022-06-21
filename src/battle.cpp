

#include <iostream>

#include "battle.hpp"
#include "display.hpp"
#include "input.hpp"
#include "rng.hpp"


Battle::Battle(const Wizard& red, const Wizard& blue)
  : player_count{ 2 }
{
  auto order = rng::RandomOrder(red, blue);

  players.push_back(order.first);
  players.push_back(order.second);

  actions.reserve(player_count);
}

void Battle::Play()
{

  while (players[0].health() > 0 && players[1].health() > 0)
  {
    RoundSetup();
    Display::Stats(players);

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
  for (Wizard& w : players) {
    w.AddPip();
  }
  actions.clear();
}

void Battle::SelectActions()
{
  for (Wizard& w : players) {
    actions.push_back(Input::SelectAction(w));
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
        Display::Pass(w);
      }
    }
  }
}