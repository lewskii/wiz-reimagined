

#include <iostream>

#include "battle.hpp"



int main()
{

  Wizard red{ "red", 513};
  Wizard blue{ "blue", 465};

  red.AddSpell({ "fire cat", 80, 75, 1 });
  red.AddSpell({ "fire bats", 245, 75, 2 });
  blue.AddSpell({ "thunder snake", 105, 70, 1 });
  blue.AddSpell({ "lightning bats", 245, 70, 2 });

  Battle duel{ red, blue };
  duel.Play();
}

