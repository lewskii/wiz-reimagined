

#include <iostream>

#include "wizard.hpp"
#include "rng.hpp"


void Cast(const Card card, Wizard &target) {
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



int main()
{
  Card fire_cat{ "fire cat", 80, 75 };
  Card thunder_snake{ "thunder snake", 105, 70 };

  Wizard red{ "red", 491};
  Wizard blue{ "blue", 449};

  std::vector<Wizard*> players;
  if (rng::AccRoll() <= 50)
  {
    players.push_back(&blue);
    players.push_back(&red);
  }
  else 
  {
    players.push_back(&red);
    players.push_back(&blue);
  }

  red.deck.push_back(fire_cat);
  blue.deck.push_back(thunder_snake);


  size_t player_count = players.size();

  while (red.health > 0 && blue.health > 0) {
    for (size_t i = 0; i < player_count; ++i) {
      Wizard w = *players[i];
      std::cout << w.name << "'s hp: " << w.health << "\n";
    }

    for (size_t i = 0; i < player_count; ++i) {
      Wizard w = *players[i];
      if (w.health > 0) {
        Cast(w.deck[0], *players[(i + 1) % player_count]);
      }
    }

    std::cin.ignore();
  }

  if (red.health > 0)
    std::cout << "red wins!\n";
  else
    std::cout << "blue wins!\n";
}

