

#include <iostream>

#include "battle.hpp"



int main()
{

  Wizard red{ "red", 513};
  Wizard blue{ "blue", 465};

  red.deck.emplace_back("fire cat", 80, 75, 1);
  red.deck.emplace_back("fire bats", 245, 75, 2);
  blue.deck.emplace_back("thunder snake", 105, 70, 1);
  blue.deck.emplace_back("lightning bats", 245, 70, 2);

  Battle duel{ red, blue };
  duel.Play();
}

