#include "input.hpp"

std::optional<Card> Input::SelectSpell(const Wizard& w)
{
  char c;
  std::cout << "select card for " << w.name() << ": ";
  std::cin >> c;
  if (isdigit(c) && c - '0' < w.stats.deck.size())
    return std::make_optional(w.stats.deck[c - '0']);
  else
    return std::nullopt;
}
