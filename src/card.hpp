#pragma once

#include <string>


class Card {
public:
  Card(
    const std::string name,
    const int damage,
    const int accuracy,
    const int pip_cost
  )
    :
    name{ name },
    damage{ damage },
    accuracy{ accuracy },
    pip_cost{ pip_cost }
  {}

  const std::string name;
  const int damage;
  const int accuracy;
  const int pip_cost;
};