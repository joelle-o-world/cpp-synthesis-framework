#include "parse.h"
using namespace std;

int measureIndent(string& line) {
  int i = 0;
  while(line[i] == ' ' || line[i] == '\t')
    ++i;
  return i;
}

std::vector<node> parseIndentedStructure(std::istream& input) {
  vector<node> nodes;
  string line;
  while(getline(input, line)) {
    cout << "A line:" << line << '\n';
    int indent = measureIndent(line);
    node newNode;
    newNode.head = line.substr(indent);
    nodes.push_back(newNode);
  }

  throw "TODO";
}


int main() {
  std::string exampleStr = "a\n  b\n  c";

  stringstream myStream(exampleStr);
  parseIndentedStructure(myStream);
}
