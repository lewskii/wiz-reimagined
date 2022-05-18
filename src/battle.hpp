#pragma once

#include <vector>

#include "rng.hpp"
#include "wizard.hpp"


class Battle final
{
public:
  Battle(Wizard red, Wizard blue)
    : player_count{ 2 }
  {
    if (rng::AccRoll() <= 50)
    {
      players.push_back(blue);
      players.push_back(red);
    }
    else
    {
      players.push_back(red);
      players.push_back(blue);
    }
  }

  void Play();


private:
  void Cast(const Card card, Wizard& target);

  void PrintStats();

  size_t player_count;
  std::vector<Wizard> players;

};

