#pragma once

#include <optional>

#include "card.hpp"


class Action {
public:
  enum class Type {
    Spell,
    Pass
  };

  Action(Card c)
    :
    type_{ Type::Spell },
    card_{ std::make_optional(c)}
  {}

  Action(std::nullopt_t _)
    :
    type_{ Type::Pass },
    card_{ std::nullopt }
  {}

  bool IsSpell() { return type_ == Type::Spell; }

  Card card() { return card_.value(); }

private:
  const Type type_;
  const std::optional<Card> card_;
};

namespace Pass {
  static const Action pass{ std::nullopt };
}
