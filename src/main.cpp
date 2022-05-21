

#include <iostream>

#include "battle.hpp"



int main()
{

  Wizard red{ "red", 513};
  Wizard blue{ "blue", 465};

  red.AddSpell({ "fire cat", 75, 1, {std::make_shared<Effect::VariableDamage>(80)} });
  red.AddSpell({ "fire elf", 75, 2, {std::make_shared<Effect::DoT>(300)} });
  red.AddSpell({ "pixie", 100, 2, {std::make_shared<Effect::Heal>(400)} });
  blue.AddSpell({ "thunder snake", 70, 1, {std::make_shared<Effect::VariableDamage>(105)} });
  blue.AddSpell({ "lightning bats", 70, 2, {std::make_shared<Effect::VariableDamage>(245)} });
  blue.AddSpell({ "spark", 100, 0, {std::make_shared<Effect::FlatDamage>(50)} });

  Battle duel{ red, blue };
  duel.Play();
}

