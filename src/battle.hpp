#pragma once

#include <vector>

#include "rng.hpp"
#include "wizard.hpp"


class Battle final
{
public:
  Battle(Wizard red, Wizard blue);

  void Play();


private:
  void RoundSetup();

  void SelectActions();

  void PlayActions();

  void PrintStats() const;

  size_t player_count;
  std::vector<Wizard> players;
  std::vector<Action> actions;

};

