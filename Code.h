#ifndef Code_H
#define Code_H
#include "Arduino.h"

class Code {
  private:
    char* content;
    int size;
    int offset = 0;
  public:
    Code(int size);
    int getSize();
    void append(char c);
    boolean isFull();
    boolean hasSpace();
    char* getValue();
    void clear();
};

#endif