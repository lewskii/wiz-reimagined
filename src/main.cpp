

#include <iostream>

#include "battle.hpp"
#include "wizardstats.hpp"



int main()
{

  WizardStats red{ "red", 513 };
  WizardStats blue{ "blue", 465 };

  Card pixie{
    "pixie",
    100,
    2,
    {std::make_shared<Heal>(400)}
  };

  red.deck.push_back({
    "fire cat",
    75,
    1,
    {std::make_shared<VariableDamage>(80)}
    });
  red.deck.push_back({
    "fire elf",
    75,
    2,
    {std::make_shared<FlatDamage>(30),
    std::make_shared<DoT>(270)}
    });
  red.deck.push_back(pixie);
  red.deck.push_back({
    "fireblade",
    100,
    0,
    {std::make_shared<Charm>(35, CharmType::Damage)}
    });

  blue.deck.push_back({
    "thunder snake",
    70,
    1,
    {std::make_shared<VariableDamage>(105)}
    });
  blue.deck.push_back({
    "lightning bats",
    70,
    2,
    {std::make_shared<VariableDamage>(245)}
    });
  blue.deck.push_back(pixie);
  blue.deck.push_back({
    "lightning strike",
    100,
    0,
    {std::make_shared<Charm>(25, CharmType::Accuracy)}
    });
  blue.deck.push_back({
    "sprite",
    100,
    1,
    {std::make_shared<Heal>(30),
    std::make_shared<HoT>(270)}
    });

  Battle duel{ red, blue };
  duel.Play();
}

