#ifndef GPIO_H
#define GPIO_H

#include <vector>

#ifdef __arm__
#include <pigpio.h>
#endif

// servos run from 400us to 2300us for 180 degrees
#define ANGLE(angle) ((((2300 - 400) / 180) * angle) + 400)
#define UNUSED(expr) (void)(expr)

namespace gpio
{

bool initPwm(const unsigned pin);
bool initIo(const unsigned pin);

bool init(const std::vector<unsigned> &pwmPins, const std::vector<unsigned> &ioPins)
{
#ifdef __arm__
    if (gpioInitialise() == PI_INIT_FAILED) {
        return false;
    }
    for (auto pin : pwmPins) {
        if (!gpio::initPwm(pin)) {
            return false;
        }
    }
    for (auto pin : ioPins) {
        if (!gpio::initIo(pin)) {
            return false;
        }
    }
#endif
    return true;
}

void shutdown()
{
#ifdef __arm__
    gpioTerminate();
#endif
}

bool initPwm(const unsigned pin)
{
#ifdef __arm__
    if (gpioSetMode(pin, PI_OUTPUT) != 0) {
        return false;
    }
    if (gpioSetPWMfrequency(pin, 50) == PI_BAD_USER_GPIO) {
        return false;
    }
    int pwmRange = gpioSetPWMrange(pin, 1e6 / 50);
    if (pwmRange == PI_BAD_USER_GPIO || pwmRange == PI_BAD_DUTYRANGE) {
        return false;
    }
#else
    UNUSED(pin);
#endif
    return true;
}

bool initIo(const unsigned pin)
{
#ifdef __arm__
    if (gpioSetMode(pin, PI_OUTPUT) != 0) {
        return false;
    }
    if (gpioWrite(pin, 0) != 0) {
        return false;
    }
#else
    UNUSED(pin);
#endif
    return true;
}

void setServo(const unsigned pin, const int angle)
{
#ifdef __arm__
    gpioPWM(pin, ANGLE(angle));
#else
    UNUSED(pin);
    UNUSED(angle);
#endif
}

void setIo(const unsigned pin, const bool state)
{
#ifdef __arm__
    gpioWrite(pin, state ? 1 : 0);
#else
    UNUSED(pin);
    UNUSED(state);
#endif
}

} // namespace gpio

#endif
