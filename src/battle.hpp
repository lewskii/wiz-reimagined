#pragma once

#include <vector>
#include <array>
#include <optional>

#include "wizard.hpp"


class Battle final
{
public:
  static constexpr size_t team_size = 4;

  typedef std::array<std::optional<Wizard>, team_size * 2> PlayerArray;

  Battle(const Wizard& red, const Wizard& blue);

  void Play();


private:
  void RoundSetup();

  void SelectActions();

  void PlayActions();

  size_t player_count;
  PlayerArray players_new;
  std::vector<Wizard> players;
  std::vector<Action> actions;

};

