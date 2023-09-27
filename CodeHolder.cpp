#include "Arduino.h"
#include "CodeHolder.h"

const char code_0[] PROGMEM = "32549";
const char code_1[] PROGMEM = "89141";
const char code_2[] PROGMEM = "77012";
const char code_3[] PROGMEM = "63203";
const char code_4[] PROGMEM = "99904";
const char code_5[] PROGMEM = "02105";
const char code_6[] PROGMEM = "80376";
const char code_7[] PROGMEM = "15978";
const char code_8[] PROGMEM = "30472";
const char code_9[] PROGMEM = "54606";
const char code_10[] PROGMEM = "00179";
const char code_11[] PROGMEM = "95621";
const char code_12[] PROGMEM = "30487";
const char code_13[] PROGMEM = "33550";
const char code_14[] PROGMEM = "62049";
const char code_15[] PROGMEM = "35100";
const char code_16[] PROGMEM = "76091";
const char code_17[] PROGMEM = "65380";
const char code_18[] PROGMEM = "62147";
const char code_19[] PROGMEM = "93015";

const char *const codes[] PROGMEM = {
  code_0,
  code_1,
  code_2,
  code_3,
  code_4,
  code_5,
  code_6,
  code_7,
  code_8,
  code_9,
  code_10,
  code_11,
  code_12,
  code_13,
  code_14,
  code_15,
  code_16,
  code_17,
  code_18,
  code_19,
};

CodeHolder::CodeHolder() {
  this->read = 0;
}

int CodeHolder::take(char* code) {
  for (int i = 0; i < 20; i++) {
    char buffer[5];
    strcpy_P(buffer, (char*) pgm_read_word(&(codes[i])));
    if (strcmp(code, buffer) == 0 && !bitRead(read, i)) {
      bitWrite(read, i, 1);
      return i;
    }
  }

  return -1;
}

boolean CodeHolder::isValid(char* code) {
  for (int i = 0; i < 20; i++) {
    char buffer[5];
    strcpy_P(buffer, (char*) pgm_read_word(&(codes[i])));
    if (strcmp(code, buffer) == 0 && !bitRead(read, i)) {
      return true;
    }
  }
  return false;
}

void CodeHolder::printBinary(long value) {
  for (int i = 31; i >= 0; i--) {
    Serial.print(bitRead(value, i));
  }
  Serial.println();
}