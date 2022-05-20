

#include <iostream>

#include "battle.hpp"



int main()
{

  Wizard red{ "red", 513};
  Wizard blue{ "blue", 465};

  auto cat_damage = Effect::VariableDamage(80);
  auto snake_damage = Effect::VariableDamage(105);
  auto bat_damage = Effect::VariableDamage(245);
  auto pixie_heal = Effect::Heal(400);
  auto spark_damage = Effect::FlatDamage(50);

  red.AddSpell({ "fire cat", 75, 1, {&cat_damage} });
  red.AddSpell({ "fire bats", 75, 2, {&bat_damage} });
  red.AddSpell({ "pixie", 100, 2, {&pixie_heal} });
  blue.AddSpell({ "thunder snake", 70, 1, {&snake_damage} });
  blue.AddSpell({ "lightning bats", 70, 2, {&bat_damage} });
  blue.AddSpell({ "spark", 100, 0, {&spark_damage} });

  Battle duel{ red, blue };
  duel.Play();
}

