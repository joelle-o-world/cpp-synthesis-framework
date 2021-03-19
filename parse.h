#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

struct node {
  std::string head;
  std::vector<node&>& children;
  node& parent;
};

std::vector<node> parseIndentedStructure(std::istream& input);


