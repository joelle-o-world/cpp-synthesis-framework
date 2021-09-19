
#include <stdlib.h>

#define tabWidth 2

const char* endOfString(const char* str) {
  while(*str)
    ++str;
  return str;
}

const char *endOfLine(const char *str) {
  while (*str && str[0] != '\n')
    str++;
  return str;
}

//char* newString(char* str) {
//}
const char *newString(const char *str, int length) {
  char *mem = (char*)malloc(length);
  memcpy(mem, str, length + 1);
  mem[length] = '\0';
  return mem;
}

const char* newString(const char* start, const char* end) {
  return newString(start, end-start);
}

const char *copyLine(const char *str) { 
  return newString(str, endOfLine(str)); 
}

void forEachLine(const char *str, void (*f)(const char *line)) {
  const char *end;
  do {
    end = endOfLine(str);
    f(newString(str, end));
    str = end;
  } while (*str);
}

bool isBlankLine(const char *str) {
  while (*str == ' ' || *str == '\t')
    ++str;
  return *str == '\n';
}

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

const char* endOfInlineWhitespace(const char* str) {
  while(*str == ' ' || *str == '\t')
    ++str;
  return str;
}

const char* endOfWhitespace(const char* str) {
  while(*str == ' ' || *str == '\t' || *str == '\n')
    ++str;
  return str;
}

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
