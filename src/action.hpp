#pragma once

#include <optional>

#include "card.hpp"


class Action {
public:
  Action(const Card& c)
    : card_{ c }
  {}

  Action(std::nullopt_t _)
    : card_{ std::nullopt }
  {}

  bool IsSpell() const { return card_.has_value(); }

  Card card() const { return card_.value(); }

private:
  const std::optional<Card> card_;
};

namespace Pass {
  static const Action pass{ std::nullopt };
}
