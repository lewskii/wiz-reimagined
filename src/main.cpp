

#include <iostream>

#include "battle.hpp"


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

  red.deck.push_back(fire_cat);
  blue.deck.push_back(thunder_snake);

  Battle duel{ red, blue };
  duel.Play();
}

