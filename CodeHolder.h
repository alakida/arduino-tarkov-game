#ifndef CodeHolder_h
#define CodeHolder_h
#include "Arduino.h"

class CodeHolder {
  private:
    long read;
    void printBinary(long value);
  public:
    CodeHolder();
    boolean isValid(char* code);
    int take(char* code);
};

#endif
