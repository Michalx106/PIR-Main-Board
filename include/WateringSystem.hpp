#pragma once
#include <Arduino.h>
#include "Button.hpp"

class WateringSystem {
public:
    WateringSystem(uint8_t pumpPin, std::shared_ptr<Button> button);

    void begin();

    void waterWhileButtonPressed();
    void waterAfterHold(unsigned long holdTime, unsigned long waterTime);

    static void handleWaterWhilePressed(WateringSystem& system);
    static void handleWaterAfterHold(WateringSystem& system, unsigned long holdTime, unsigned long waterTime);

private:
    uint8_t pumpPin;
    std::shared_ptr<Button> button;

    unsigned long wateringStartTime = 0;
    bool isWatering = false;
};
