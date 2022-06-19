#include "input.hpp"

Action Input::SelectAction(const Wizard& w)
{
  char c;
  std::cout << "select card for " << w.name() << ": ";
  std::cin >> c;
  if (isdigit(c) && c - '0' < w.stats.deck.size())
    return Action(w.stats.deck[c - '0']);
  else
    return Pass::pass;
}
