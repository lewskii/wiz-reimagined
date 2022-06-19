#pragma once

#include "card.hpp"

struct WizardStats {
public:
  WizardStats(std::string name, School school, int hp)
    :
    name{ name },
    school{ school },
    max_health{ hp },
    health{ hp }
  {}

  const std::string name;
  const School school;
  int max_health;
  int health;

  std::vector<Card> deck;
};
