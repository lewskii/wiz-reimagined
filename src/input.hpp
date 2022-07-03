#pragma once

#include <iostream>
#include <optional>

#include "wizard.hpp"


class Input {
public:
  Input() = delete;

  static std::optional<Card> SelectSpell(const Wizard& w);

};
