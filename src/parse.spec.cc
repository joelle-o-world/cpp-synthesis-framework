# include <iostream>
# include <cassert>
#include <stdlib.h>

# include "./parse.h"

// Use (void) to silent unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

int main() {
  std::cout << "\n\n";

  const char* exampleStr = "Hello,\n\tworld!";
  const char* example2 = "*\n  osc\n  .5\nosc";
  std::vector<const char*> example2SubSections = {
    "  osc",
    "  .5"
  };

  // endOfString
  assert(
    endOfString(exampleStr) == (exampleStr + strlen(exampleStr))
  );

  // endOfLine
  assert(
    endOfLine(exampleStr) - exampleStr == 7
  );

  // TODO: newString
  // TODO: copyLine
  // TODO: forEachLine

  // isBlankLine
  assert(isBlankLine("\n"));
  assert(!isBlankLine("hello!"));

  // measureIndent
  assert(measureIndent(exampleStr) == 0);
  assert(measureIndent("  hiii") == 2);

  // endOfIndentedSection
  assert(endOfIndentedSection(example2) - example2 == 13);

  // copyIndentedSection
  assert(
    strcmp(copyIndentedSection(example2) , "*\n  osc\n  .5")
  );

  // copyIndentedBody
  assert(
    strcmp(copyIndentedBody(example2), "  osc\n  .5")
  );

  // listIndentedSubSections

  std::cout << listIndentedSubSections(example2) << "\n\n";
  assert(
    *listIndentedSubSections(example2) == example2SubSections
  );

  

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
