#include "mp3tf16p.h"
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "CodeHolder.h"
#include "Code.h"

const int LCD_ADDRESS = 0x27;
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

const int INCORRECT_CODE_FILE_ID = 21;
const int EXIT_INTRO_FILE_ID = 22;

CodeHolder codeHolder;

const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte rowPins[rows] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[cols] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
MP3Player mp3Player(10, 11);

Code code(5);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println(F("INFO: Setup started"));
  lcd.init(); //Инициализация LCD (по умолчанию для ESP8266: 4 - SDA, 5 - SCL)
  lcd.backlight();
  lcd.clear();
  mp3Player.initialize();
  Serial.println(F("INFO: Setup finished"));
}

void loop() {
  lcd.clear();
  lcd.print("->VVEDITE  KOD<-");
  lcd.setCursor(6, 1);
  lcd.print("*****");
  Serial.println("Waiting for the code...");
  
  while (code.hasSpace()) {
    char key = keypad.waitForKey();
    code.append(key);
    lcd.setCursor(6, 1);
    lcd.print(code.getValue());
  }
  
  Serial.println(code.getValue());
  
  if (codeHolder.isValid(code.getValue())) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pravilnii kod!");
    int response = codeHolder.take(code.getValue());
    Serial.println("Code is correct!");
    playFile(EXIT_INTRO_FILE_ID);
    playFile(response);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Nepravilnii kod!");
    Serial.println("Code is not valid or has been used");
    playFile(INCORRECT_CODE_FILE_ID);
  }

  code.clear();
}

void playFile(int code) {
  Serial.print("Playing file ");
  Serial.println(code + 1, DEC);
  mp3Player.playTrackNumber(code + 1, 20);
}
