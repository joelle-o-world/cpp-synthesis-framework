#pragma once

#include <stdlib.h>
#include <vector>

#include "./utils.h"

#define tabWidth 2





short int measureIndent(const char *str) {
  short int indent = 0;
  while (*str) {
    char c = *str;
    if (c == ' ')
      ++indent;
    else if (c == '\t')
      indent += tabWidth;
    else
      break;
    ++str;
  }
  return indent;
}

const char *endOfIndentedSection(const char *str) {
  short int indent = measureIndent(str);
  do {
    str = endOfLine(str);
  } while (*str && (isBlankLine(str) || measureIndent(str) > indent));

  return str;
}

const char *copyIndentedSection(const char *str) {
  return newString(str, endOfIndentedSection(str));
}

const char *copyIndentedBody(const char* str) {
  return newString(endOfLine(str),  endOfIndentedSection(str));
}

std::vector<const char*> * listIndentedSubSections(const char* str) {
  const char* end = endOfIndentedSection(str);
  const char* next;
  std::vector< const char*>* out = new std::vector<const char*>;
  str = endOfLine(str);
  while(str < end) {
    next = endOfIndentedSection(str);
    out->push_back(newString(str, next));
    //out\>push (newString(str, next));
    str = next;
  }
  return out;
}

void forEachIndentedSection(
  const char *str, 
  void (*f)(const char *indentedSection, void* passAlong),
  void* passAlong
) {
  short int indent = measureIndent(str);
  const char *end;
  do {
    end = endOfIndentedSection(str);
    f(newString(str, end), passAlong);
    str = end;
  } while (*str && measureIndent(str) == indent);
}

void forEachIndentedSection(
  const char *str, 
  void (*f)(const char *indentedSection)
) {
  short int indent = measureIndent(str);
  const char *end;
  do {
    end = endOfIndentedSection(str);
    f(newString(str, end));
    str = end;
  } while (*str && measureIndent(str) == indent);
}

typedef struct {
  const char* header;
  const char* body;
} IndentedSection;

IndentedSection parseIndentedSection(char*   start) {
  const char* end = endOfIndentedSection(start);
  const char* headerEnd = endOfLine(start);

  IndentedSection out = {newString(start, headerEnd),
   newString(headerEnd, end)
  };

  return out;
}
