#pragma once


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

bool isBlankLine(const char *str) {
  while (*str == ' ' || *str == '\t')
    ++str;
  return *str == '\n';
}

const char *newString(const char *str, int length) {
  char *mem = (char*)malloc(length);
  memcpy(mem, str, length + 1);
  mem[length] = '\0';
  return mem;
}

const char* newString(const char* start, const char* end) {
  return newString(start, end-start);
}

const char* endOfString(const char* str) {
  while(*str)
    ++str;
  return str;
}

const char *endOfLine(const char *str) {
  if(*str == '\0')
    return nullptr;
  do {
    str++;
  } while (*str && str[0] != '\n');
  return str+1;
}

//char* newString(char* str) {
//}


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
