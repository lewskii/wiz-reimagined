

#include <iostream>

#include "battle.hpp"



int main()
{
  Card fire_cat{ "fire cat", 80, 75, 1 };
  Card thunder_snake{ "thunder snake", 105, 70, 1 };

  Wizard red{ "red", 491};
  Wizard blue{ "blue", 449};

  red.deck.push_back(fire_cat);
  blue.deck.push_back(thunder_snake);

  Battle duel{ red, blue };
  duel.Play();
}

