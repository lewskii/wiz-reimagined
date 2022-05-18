#pragma once

#include <optional>

#include "card.hpp"


struct Action {
public:
  enum class Type {
    Spell,
    Pass
  };

  Action(Card c)
    :
    type{ Type::Spell },
    card{ std::make_optional(c)}
  {}

  Action(std::nullopt_t _)
    :
    type{ Type::Pass },
    card{ std::nullopt }
  {}

  const Type type;
  const std::optional<Card> card;
};

namespace Pass {
  static const Action pass{ std::nullopt };
}
