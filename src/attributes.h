#pragma once

#include "parse.h"

const char* startOfAttributeName(const char* str) {
  return endOfInlineWhitespace(str);
}

const char* endOfAttributeName(const char* str) {
  const char* end = str;
  while(*end != ':')
    if(*end == '\n' || !*end)
      return nullptr;

  // Otherwise
  return end;
}

const char* copyAttributeName(const char* str) {
  const char* start = startOfAttributeName(str);
  const char* end = endOfAttributeName(str);
  return newString(start, end);
}

const char* startOfAttributeValue(const char* startOfLine) {
  return endOfWhitespace(endOfAttributeName(startOfLine) + 1);
}

const char* endOfAttributeValue(const char* startOfLine) {
  return endOfIndentedSection(startOfLine);
}

const char* copyAttributeValue(const char* startOfLine) {
  return newString(startOfAttributeValue(startOfLine), endOfAttributeValue(startOfLine));
}


// TODO: attributeValue
