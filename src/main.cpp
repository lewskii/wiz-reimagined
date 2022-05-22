

#include <iostream>

#include "battle.hpp"
#include "wizardstats.hpp"



int main()
{

  WizardStats red{ "red", 513 };
  WizardStats blue{ "blue", 465 };

  red.deck.push_back({
    "fire cat",
    75,
    1,
    {std::make_shared<Effect::VariableDamage>(80)}
    });
  red.deck.push_back({
    "fire elf",
    75,
    2,
    {std::make_shared<Effect::FlatDamage>(30),
    std::make_shared<Effect::DoT>(270)}
    });
  red.deck.push_back({
    "pixie",
    100,
    2,
    {std::make_shared<Effect::Heal>(400)}
    });
  blue.deck.push_back({
    "thunder snake",
    70,
    1,
    {std::make_shared<Effect::VariableDamage>(105)}
    });
  blue.deck.push_back({
    "lightning bats",
    70,
    2,
    {std::make_shared<Effect::VariableDamage>(245)}
    });
  blue.deck.push_back({
    "spark",
    100,
    0,
    {std::make_shared<Effect::FlatDamage>(50)}
    });

  Battle duel{ red, blue };
  duel.Play();
}

