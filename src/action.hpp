#pragma once

#include <optional>

#include "card.hpp"


class Action {
public:
  Action(const Card& c)
    : card_{ c }
  {}

  Action(const std::optional<Card>& c)
    : card_{ c }
  {}

  bool IsSpell() const { return card_.has_value(); }

  Card card() const { return card_.value(); }

private:
  const std::optional<Card> card_;
};

namespace Pass {
  static const Action pass{ std::nullopt };
}
