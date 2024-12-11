#include "WateringSystem.hpp"

WateringSystem::WateringSystem(uint8_t pumpPin, std::shared_ptr<Button> button)
    : pumpPin(pumpPin), button(button) {}

void WateringSystem::begin() {
    pinMode(pumpPin, OUTPUT);
    digitalWrite(pumpPin, LOW);
}

void WateringSystem::waterWhileButtonPressed() {
    button->CheckState() ? digitalWrite(button->getPinNumber(), HIGH) : digitalWrite(button->getPinNumber(), LOW);
}

void WateringSystem::waterAfterHold(unsigned long holdTime, unsigned long waterTime) {
    unsigned long pressDuration = button->getPressDuration();

    if (pressDuration >= holdTime && !isWatering) {
        digitalWrite(pumpPin, HIGH);
        isWatering = true;
        wateringStartTime = millis();
    }

    if (isWatering && millis() - wateringStartTime >= waterTime) {
        digitalWrite(pumpPin, LOW);
        isWatering = false;
    }
}

void WateringSystem::handleWaterWhilePressed(WateringSystem& system) {
    system.waterWhileButtonPressed();
}

void WateringSystem::handleWaterAfterHold(WateringSystem& system, unsigned long holdTime, unsigned long waterTime) {
    system.waterAfterHold(holdTime, waterTime);
}