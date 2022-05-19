

#include <iostream>

#include "battle.hpp"



int main()
{

  Wizard red{ "red", 513};
  Wizard blue{ "blue", 465};

  red.AddSpell({ "fire cat", 75, 1, Effect::Damage(80) });
  red.AddSpell({ "fire bats", 75, 2, Effect::Damage(245) });
  blue.AddSpell({ "thunder snake", 70, 1, Effect::Damage(105) });
  blue.AddSpell({ "lightning bats", 70, 2, Effect::Damage(245) });

  Battle duel{ red, blue };
  duel.Play();
}

