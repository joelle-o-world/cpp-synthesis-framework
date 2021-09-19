# include <iostream>
# include <cassert>
#include <stdlib.h>

# include "./parse.h"

// Use (void) to silent unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

int main() {
  std::cout << "\n\n";

  const char* exampleStr = "Hello,\n\tworld!";

  // endOfString
  assert(
    endOfString(exampleStr) == (exampleStr + strlen(exampleStr))
  );

  // endOfLine
  assert(
    endOfLine(exampleStr) - exampleStr == 6
  );

  // TODO: newString
  // TODO: copyLine
  // TODO: forEachLine
  // TODO: isBlankLine

  // measureIndent
  assert(measureIndent(exampleStr) == 0);
  assert(measureIndent("  hiii") == 2);

  // TODO: endOfIndentedSection
  // TODO: copyIndentedSection
  // TODO: forEachIndentedSection
  // TODO: forEachIndentedSection
  // TODO: endOfInlineWhitespace
  // TODO: endOfWhitespace
  // TODO: startOfAttributeName
  // TODO: endOfAttributeName
  // TODO: copyAttributeName
  // TODO: startOfAttributeValue
  // TODO: endOfAttributeValue
  // TODO: copyAttributeValue

  std::cout << "All tests passed";
}
