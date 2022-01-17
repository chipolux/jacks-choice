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

std::vector<Event> EVENTS{
    // start with neck forward, mouth closed, and brain off
    {Event::Neck, 0},
    {Event::Mouth, 0},
    {Event::Brain, 0},

    {Event::Neck, 1850, 15},
    {Event::Mouth, 1900, MOUTH_OPEN}, // love (open) (200ms)
    {Event::Mouth, 2100},

    {Event::Neck, 2300, -18},
    {Event::Brain, 2350, 1},
    {Event::Mouth, 2350, MOUTH_OPEN}, // brain (open) (250ms)
    {Event::Mouth, 2600},
    {Event::Brain, 2800},

    {Event::Neck, 2850, 20},
    {Event::Mouth, 2900, MOUTH_OPEN}, // heart (open) (150ms)
    {Event::Mouth, 3050},

    {Event::Neck, 3200},
    {Event::Mouth, 3250, MOUTH_OPEN},    // con- (open)
    {Event::Mouth, 3300, MOUTH_PARTIAL}, // -tr- (partial)
    {Event::Mouth, 3500, MOUTH_OPEN},    // -o- (open)
    {Event::Mouth, 3700},                // -l (close)

    {Event::Mouth, 3795, MOUTH_OPEN},    // ca- (open)
    {Event::Mouth, 3845, MOUTH_PARTIAL}, // -ff- (partial)
    {Event::Mouth, 3995, MOUTH_OPEN},    // -ei- (open)
    {Event::Mouth, 4100, MOUTH_PARTIAL}, // -n- (partial)
    {Event::Mouth, 4200, MOUTH_OPEN},    // -a- (open)
    {Event::Mouth, 4400},                // -te (close)

    {Event::Mouth, 4829, MOUTH_OPEN},    // mel- (open)
    {Event::Mouth, 5060, MOUTH_PARTIAL}, // -a- (partial)
    {Event::Mouth, 5320, MOUTH_OPEN},    // -ton- (open)
    {Event::Mouth, 5600},                // -in (close)

    {Event::Mouth, 5808, MOUTH_OPEN}, // love (open)
    {Event::Mouth, 6000},

    {Event::Mouth, 6762, MOUTH_OPEN}, // heart (open)
    {Event::Mouth, 6900},

    {Event::Mouth, 7191, MOUTH_PARTIAL}, // con- (partial)
    {Event::Mouth, 7280, MOUTH_OPEN},    // -tro- (open)
    {Event::Mouth, 7400},                // -l (close)

    {Event::Mouth, 7705, MOUTH_OPEN},    // ca- (open)
    {Event::Mouth, 7755, MOUTH_PARTIAL}, // -ff- (partial)
    {Event::Mouth, 7905, MOUTH_OPEN},    // -ei- (open)
    {Event::Mouth, 8100, MOUTH_PARTIAL}, // -n- (partial)
    {Event::Mouth, 8150, MOUTH_OPEN},    // -a- (open)
    {Event::Mouth, 8350},                // -te (close)

    {Event::Mouth, 8440, MOUTH_OPEN}, // you (open)
    {Event::Mouth, 8540},

    {Event::Mouth, 8670, MOUTH_OPEN}, // get (open)
    {Event::Mouth, 8740},

    {Event::Mouth, 8919, MOUTH_OPEN}, // me (open)
    {Event::Mouth, 9000},

    {Event::Mouth, 9163, MOUTH_OPEN}, // going (open)
    {Event::Mouth, 9363},

    {Event::Brain, 10115, 1},
    {Event::Mouth, 10115, MOUTH_OPEN}, // brain (open)
    {Event::Mouth, 10365},
    {Event::Brain, 10600},

    {Event::Mouth, 10604, MOUTH_OPEN}, // heart (open)
    {Event::Mouth, 10854},

    {Event::Mouth, 11030, MOUTH_PARTIAL}, // con- (partial)
    {Event::Mouth, 11120, MOUTH_OPEN},    // -tro- (open)
    {Event::Mouth, 11240},                // -l (close)

    {Event::Mouth, 11599, MOUTH_OPEN},    // ca- (open) (50ms)
    {Event::Mouth, 11650, MOUTH_PARTIAL}, // -ff- (partial) (150ms)
    {Event::Mouth, 11800, MOUTH_OPEN},    // -ei- (open) (105ms)
    {Event::Mouth, 11905, MOUTH_PARTIAL}, // -n- (partial) (100ms)
    {Event::Mouth, 12005, MOUTH_OPEN},    // -a- (open) (200ms)
    {Event::Mouth, 12205},                // -te (close)

    {Event::Mouth, 12518, MOUTH_OPEN},    // mel- (open) (230ms)
    {Event::Mouth, 12750, MOUTH_PARTIAL}, // -a- (partial) (260ms)
    {Event::Mouth, 13010, MOUTH_OPEN},    // -ton- (open) (280ms)
    {Event::Mouth, 13290},                // -in (close)

    {Event::Mouth, 13518, MOUTH_OPEN}, // love (open) (200ms)
    {Event::Mouth, 13720},

    {Event::Brain, 13948, 1},
    {Event::Mouth, 13948, MOUTH_OPEN}, // brain (open) (250ms)
    {Event::Mouth, 14200},
    {Event::Brain, 14350},

    {Event::Mouth, 14387, MOUTH_OPEN}, // heart (open) (150ms)
    {Event::Mouth, 14530},

    {Event::Mouth, 15368, MOUTH_OPEN}, // wake (open)
    {Event::Mouth, 15440},

    {Event::Mouth, 15617, MOUTH_OPEN}, // up (open)
    {Event::Mouth, 15700},

    {Event::Mouth, 16078},     // (ss-)
    {Event::Neck, 16343, -50}, // (-mack)
    {Event::Mouth, 16343},     // (-mack)
    {Event::Neck, 16844},
    {Event::Mouth, 16844}, // (end of wiggly bit)
    {Event::Mouth, 17748}, // nice
    {Event::Mouth, 18028}, // to
    {Event::Mouth, 18198}, // meet
    {Event::Mouth, 18484}, // ya
    {Event::Mouth, 19199}, // who
    {Event::Mouth, 19455}, // could
    {Event::Mouth, 19613}, // you
    {Event::Mouth, 19970}, // be
    {Event::Mouth, 21159}, // i
    {Event::Mouth, 21615}, // am
    {Event::Mouth, 22101}, // in-
    {Event::Mouth, 22514}, // -jur-
    {Event::Mouth, 22841}, // -y
    {Event::Mouth, 24487}, // no
    {Event::Mouth, 24685}, // you
    {Event::Mouth, 24982}, // aren't
    {Event::Mouth, 25695}, // you
    {Event::Mouth, 25924}, // made
    {Event::Mouth, 26428}, // the
    {Event::Mouth, 26878}, // choice
    {Event::Mouth, 27373}, // to
    {Event::Mouth, 27647}, // be
    {Event::Mouth, 28296}, // but
    {Event::Mouth, 28592}, // i
    {Event::Mouth, 28809}, // am
    {Event::Mouth, 29389}, // no
    {Event::Mouth, 29637}, // i
    {Event::Mouth, 29896}, // am
    {Event::Mouth, 30439}, // no
    {Event::Mouth, 30736}, // do-
    {Event::Mouth, 30927}, // -pa-
    {Event::Mouth, 31044}, // -mine
    {Event::Mouth, 31569}, // eh--
};

#endif
