#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Button.hpp"
#include "EspNowManager.hpp"
#include "WateringSystem.hpp"

#define PUMP_PIN 5
#define BUTTON_PIN 23

auto button = std::make_shared<Button>(BUTTON_PIN, INPUT_PULLUP);
auto lcd = std::make_shared<LiquidCrystal_I2C>(0x27, 16, 2);
auto wateringSystem = std::make_shared<WateringSystem>(PUMP_PIN, button, lcd);

LiquidCrystal_I2C lcd(0x27,20,4);

EspNowManager espNow;
uint8_t peerAddress[] = {0x24, 0x6F, 0x28, 0x28, 0x28, 0x28};

void setup() {
    Serial.begin(115200);
    wateringSystem->begin();
}

void loop() {
  Button::LoopFunction(button, 3000, WateringSystem::handleWaterWhilePressed);
  Button::LoopFunction(button, 3000, WateringSystem::handleWaterAfterHold, 3000, 30000);
  
}
