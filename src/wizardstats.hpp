#pragma once

#include "card.hpp"

struct WizardStats {
public:
  WizardStats(std::string name, School school, int hp, int pip_chance)
    :
    name{ name },
    school{ school },
    max_health{ hp },
    health{ hp },
    pip_chance{ pip_chance }
  {}

  const std::string name;
  const School school;
  int max_health;
  int health;
  int pip_chance;

  std::vector<Card> deck;
};
