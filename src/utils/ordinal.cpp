#include "ordinal.h"

std::string ordinal(int n) {
  ++n;
  if (n == 11 || n == 12 || n == 13)
    return std::to_string(n) + "th";
  else {
    if (n % 10 == 1)
      return std::to_string(n) + "st";
    else if (n % 10 == 2)
      return std::to_string(n) + "nd";
    else if (n % 10 == 3)
      return std::to_string(n) + "rd";
    else
      return std::to_string(n) + "th";
  }
}
