#pragma once

#include "card.hpp"

struct WizardStats {
public:
  WizardStats(const std::string name, const int hp)
    :
    name{ name },
    max_health{ hp },
    health{ hp }
  {}

  const std::string name;
  int max_health;
  int health;

  std::vector<Card> deck;
};
