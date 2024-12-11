#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Button.hpp"
#include "EspNowManager.hpp"
#include "WateringSystem.hpp"

#define PUMP_PIN 5
#define BUTTON1_PIN 23

std::shared_ptr<Button> button1(new Button(BUTTON1_PIN, INPUT_PULLDOWN));
WateringSystem wateringSystem(PUMP_PIN, button1);

LiquidCrystal_I2C lcd(0x27,20,4);

EspNowManager espNow;
uint8_t peerAddress[] = {0x24, 0x6F, 0x28, 0x28, 0x28, 0x28};

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
  Button::LoopFunction(button1, 3000, WateringSystem::handleWaterWhilePressed);
  Button::LoopFunction(button1, 3000, WateringSystem::handleWaterAfterHold, 3000, 30000);
  
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
