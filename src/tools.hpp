#pragma once

#include <string>

static std::string SignedNumString(int n)
{
  if (n < 0)
    return std::to_string(n);
  else
    return "+" + std::to_string(n);
}
