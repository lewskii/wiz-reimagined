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

  void Cast(Wizard& caster, const Card& card, Wizard& target);

  void PrintStats();

  size_t player_count;
  std::vector<Wizard> players;
  std::vector<Action> actions;

};

