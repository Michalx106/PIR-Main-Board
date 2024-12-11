#include "button.hpp"

Button::Button(u_int8_t pinDefinition, u_int8_t mode)
{
    pinNumber = pinDefinition;
    mode = mode;
    lastClick = millis();
    instances.push_back(shared_from_this());
}

bool Button::Init()
{
    pinMode(pinNumber, mode);
}

bool Button::InitAll()
{
    for (const auto& instance : instances) {
        instance->Init();
    }
}

u_int8_t Button::getPinNumber()
{
    return pinNumber;
}

u_int8_t Button::getPinNumber(Button button)
{
    return button.pinNumber;
}

unsigned long Button::getTimeBetweenClicks()
{
    return timeBetweenClick;
}

unsigned long Button::setNewTimeBetweenClicks()
{
    unsigned long time = millis() - lastClick;
    lastClick = millis();
    return time;
}

bool Button::CheckState()
{
    return digitalRead(pinNumber) ? true : false;
}

template <typename T, typename... Args>
void Button::LoopFunction(Button button, unsigned long interval, T func, Args... args)
{
    state = CheckState();
    timeBetweenClick = setNewTimeBetweenClicks();

    if(timeBetweenClick >= interval && state) func(args);
}