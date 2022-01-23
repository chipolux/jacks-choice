#ifndef CHOICE_HPP
#define CHOICE_HPP

#include <vector>

#include "gpio.hpp"

#define TEMPO_MS 477

// pinout
#define MOUTH_UPPER 14
#define MOUTH_LOWER 15
#define NECK 18
#define BRAIN_WIRE 23

// common angles
#define MOUTH_PARTIAL 8
#define MOUTH_OPEN 15

const std::vector<unsigned> PWM_PINS = {MOUTH_UPPER, MOUTH_LOWER, NECK};
const std::vector<unsigned> IO_PINS = {BRAIN_WIRE};

class Event
{
  public:
    enum Type {
        None,
        Mouth,
        Neck,
        Brain,
    };

    Event(Type type, unsigned long ms = 0, int value = 0, bool abort = false)
        : type(type)
        , ms(ms)
        , value(value)
        , abort(abort)
    {
    }

    void run() const
    {
        switch (type) {
        case None:
            break;
        case Mouth: {
            gpio::setServo(MOUTH_UPPER, 180 - value);
            gpio::setServo(MOUTH_LOWER, 0 + value);
            break;
        };
        case Neck: {
            gpio::setServo(NECK, 90 + value);
            break;
        };
        case Brain: {
            gpio::setIo(BRAIN_WIRE, value > 0 ? true : false);
            break;
        };
        }
    }

    const Type type;
    const unsigned long ms;
    const int value;
    const bool abort;
};

// include events expored from blender animation
#include "exported_events.hpp"

#endif
