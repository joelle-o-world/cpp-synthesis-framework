
#include <stdlib.h>

#define tabWidth 2

char* endOfString(char* str) {
  while(*str)
    ++str;
  return str;
}

char *endOfLine(char *str) {
  while (*str && str[0] != '\n')
    str++;
  return str;
}

char* newString(char* str) {
}
char *newString(char *str, int length) {
  char *mem = malloc(length);
  memcpy(mem, str, length + 1);
  mem[length] = '\0';
  return mem;
}

char* newString(char* start, char* end) {
  return newString(start, end-start);
}

char *copyLine(char *str) { return newString(str, endOfLine(str)); }

void forEachLine(char *str, void (*f)(char *line)) {
  char *end;
  do {
    end = endOfLine(str);
    f(newString(str, end));
    str = end;
  } while (*str);
}

bool isBlankLine(char *str) {
  while (*str == ' ' || *str == '\t')
    ++str;
  return *str == '\n';
}

short int measureIndent(char *str) {
  short int indent = 0;
  while (*str) {
    char c = *str;
    if (c == ' ')
      ++indent;
    else if (c == '\t')
      indent += tabWidth;
    else
      break;
  }
  return indent;
}

char *endOfIndentedSection(char *str) {
  short int indent = measureIndent(str);
  do {
    str = endOfLine(str);
  } while (*str && (isBlankLine(str) || measureIndent(str) > indent));

  return str;
}

char *copyIndentedSection(char *str) {
  return newString(str, endOfIndentedSection(str));
}

void forEachIndentedSection(
  char *str, 
  void (*f)(char *indentedSection, void* passAlong),
  void* passAlong
) {
  short int indent = measureIndent(str);
  char *end;
  do {
    end = endOfIndentedSection(str);
    f(newString(str, end), passAlong);
    str = end;
  } while (*str && measureIndent(str) == indent);
}

void forEachIndentedSection(
  char *str, 
  void (*f)(char *indentedSection)
) {
  short int indent = measureIndent(str);
  char *end;
  do {
    end = endOfIndentedSection(str);
    f(newString(str, end));
    str = end;
  } while (*str && measureIndent(str) == indent);
}

char* endOfInlineWhitespace(char* str) {
  while(*str == ' ' || *str == '\t')
    ++str;
  return str;
}

char* endOfWhitespace(char* str) {
  while(*str == ' ' || *str == '\t' || *str == '\n')
    ++str;
  return str;
}

char* startOfAttributeName(char* str) {
  return endOfInlineWhitespace(str);
}

char* endOfAttributeName(char* str) {
  char* end = str;
  while(*end != ':')
    if(*end == '\n' || !*end)
      return nullptr;

  // Otherwise
  return end;
}

char* copyAttributeName(char* str) {
  char* start = startOfAttributeName(str);
  char* end = endOfAttributeName(str);
  return newString(start, end);
}

char* startOfAttributeValue(char* startOfLine) {
  return endOfWhitespace(endOfAttributeName(startOfLine) + 1);
}

char* endOfAttributeValue(char* startOfLine) {
  return endOfIndentedSection(startOfLine);
}

char* copyAttributeValue(char* startOfLine) {
  return newString(startOfAttributeValue(startOfLine), endOfAttributeValue(startOfLine));
}

// TODO: attributeValue
