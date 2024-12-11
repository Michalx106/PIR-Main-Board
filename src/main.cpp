#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Button.hpp"
#include "EspNowManager.hpp"

#define transitorBase 5
std::shared_ptr<Button> button1(new Button(23, INPUT_PULLUP));

LiquidCrystal_I2C lcd(0x27,20,4);

EspNowManager espNow;
uint8_t peerAddress[] = {0x24, 0x6F, 0x28, 0x28, 0x28, 0x28};

// put function declarations here:
int myFunction(int, int);

void setup() {
  Button::InitAll();
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
}

void loop() {
  int x,y;
  Button::LoopFunction(*button1, 0, myFunction, x,y);
  
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}