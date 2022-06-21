

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

    SelectActions();
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

Battle::Winner Battle::CheckWinner() const
{
  int result = 0;
  if (!players.at(0).IsActive()) result += 1;
  if (!players.at(1).IsActive()) result += 2;
  auto test = static_cast<Winner>(result);
  return test;
}
