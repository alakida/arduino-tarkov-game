#include "Arduino.h"
#include "Code.h"

Code::Code(int size) {
  this->size = size;
  this->content = new char[size + 1];
  this->clear();
}

int Code::getSize() {
  return size;
}

void Code::append(char c) {
  content[offset] = c;
  offset++;
}

boolean Code::isFull() {
  return offset >= size;
}

boolean Code::hasSpace() {
  return !this->isFull();
}

char* Code::getValue() {
  return content;
}

void Code::clear() {
  offset = 0;
  for (int i = 0; i <= size; i++) {
    content[i] = '\0';
  }
}