#pragma once

#include <vector>
#include <array>
#include <optional>

#include "wizard.hpp"


class Battle final
{
public:
  enum class Winner {
    None,
    Red,
    Blue,
    Draw
  };

  static constexpr size_t team_size = 4;

  typedef std::array<std::optional<Wizard>, team_size * 2> PlayerArray;

  Battle(const Wizard& red, const Wizard& blue);

  void Play();


private:
  void RoundSetup();
  void SelectSpells();
  void PlayActions();


  void Cast(Wizard& caster, const Card& card, Wizard& target);
  void CastSuccess(Wizard& caster, const Card& card, Wizard& target);

  void ResolveCardEffects(
    Wizard& caster,
    const Card& card,
    Wizard& target,
    double damage_modifier,
    double heal_modifier
  );


  Winner CheckWinner() const;


  size_t player_count;
  PlayerArray players_new;
  std::vector<Wizard> players;
  std::vector<Action> actions;

};

