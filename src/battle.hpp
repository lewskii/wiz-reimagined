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
  void Cast(const Card card, Wizard& target) {
    if (rng::AccRoll() <= card.accuracy)
    {
      int damage = target.DealDamage(card.damage + rng::DamageRoll() * 10);
      std::cout << target.name << " took " << damage << " damage from " << card.name << "!\n";
      if (target.health == 0)
        std::cout << target.name << " has been defeated!\n";
    }
    else
    {
      std::cout << card.name << " fizzled!\n";
    }
  }

  size_t player_count;
  std::vector<Wizard> players;

};

