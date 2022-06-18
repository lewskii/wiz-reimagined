

#include <iostream>

#include "battle.hpp"
#include "wizardstats.hpp"



int main()
{

  WizardStats red{ "red", 513 };
  WizardStats blue{ "blue", 465 };

  Card pixie{
    "pixie",
    School::Life,
    100,
    2,
    {std::make_shared<Heal>(400)}
  };

  Card sprite{
    "sprite",
    School::Life,
    100,
    1,
    {std::make_shared<Heal>(30),
    std::make_shared<HoT>(270)}
  };

  red.deck.push_back({
    "fire cat",
    School::Fire,
    75,
    1,
    {std::make_shared<VariableDamage>(80)}
    });
  red.deck.push_back({
    "fire elf",
    School::Fire,
    75,
    2,
    {std::make_shared<FlatDamage>(30),
    std::make_shared<DoT>(270)}
    });
  red.deck.push_back(pixie);
  red.deck.push_back({
    "fireblade",
    School::Fire,
    100,
    0,
    {std::make_shared<Charm>(35, HangingEffectDomain::Damage)}
    });
  red.deck.push_back(sprite);

  blue.deck.push_back({
    "thunder snake",
    School::Storm,
    70,
    1,
    {std::make_shared<VariableDamage>(105)}
    });
  blue.deck.push_back({
    "lightning bats",
    School::Storm,
    70,
    2,
    {std::make_shared<VariableDamage>(245)}
    });
  blue.deck.push_back(pixie);
  blue.deck.push_back({
    "lightning strike",
    School::Storm,
    100,
    0,
    {std::make_shared<Charm>(25, HangingEffectDomain::Accuracy)}
    });
  blue.deck.push_back(sprite);

  Battle duel{ red, blue };
  duel.Play();
}

