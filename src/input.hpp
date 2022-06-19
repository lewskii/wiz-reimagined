#pragma once

#include <iostream>

#include "wizard.hpp"


class Input {
public:
  Input() = delete;

  static Action SelectAction(const Wizard& w);

};
