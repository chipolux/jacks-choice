#ifndef CHOICE_HPP
#define CHOICE_HPP

#include <vector>

#define ANGLE(angle) ((((2300 - 400) / 180) * angle) + 400)
#define TEMPO_MS 477

// servo pins
#define MOUTH_UPPER 14
#define MOUTH_LOWER 15
#define NECK 18

enum MouthState : unsigned { Closed = 0, Partial = 8, Open = 15 };

struct MouthEvent {
    const unsigned long ms;
    const MouthState state;
    const int upperAngle;
    const int lowerAngle;
    const bool abort;

    MouthEvent(unsigned long ms, MouthState state = MouthState::Closed, bool abort = false)
        : ms(ms)
        , state(state)
        , upperAngle(180 - state)
        , lowerAngle(0 + state)
        , abort(abort)
    {
    }
};

struct NeckEvent {
    const unsigned long ms;
    const int angle;
    const bool abort;

    NeckEvent(unsigned long ms, int angle = 90, bool abort = false)
        : ms(ms)
        , angle(angle)
        , abort(abort)
    {
    }
};

const std::vector<MouthEvent> mouthEvents = {
    {0}, // (start closed)

    {1900, MouthState::Open}, // love (open) (200ms)
    {2100},                   // (close)

    {2350, MouthState::Open}, // brain (open) (250ms)
    {2600},                   // (close)

    {2900, MouthState::Open}, // heart (open) (150ms)
    {3050},                   // (close)

    {3250, MouthState::Open},    // con- (open)
    {3300, MouthState::Partial}, // -tr- (partial)
    {3500, MouthState::Open},    // -o- (open)
    {3700},                      // -l (close)

    {3795, MouthState::Open},    // ca- (open)
    {3845, MouthState::Partial}, // -ff- (partial)
    {3995, MouthState::Open},    // -ei- (open)
    {4100, MouthState::Partial}, // -n- (partial)
    {4200, MouthState::Open},    // -a- (open)
    {4400},                      // -te (close)

    {4829, MouthState::Open},    // mel- (open)
    {5060, MouthState::Partial}, // -a- (partial)
    {5320, MouthState::Open},    // -ton- (open)
    {5600},                      // -in (close)

    {5808, MouthState::Open}, // love (open)
    {6000},                   // (close)

    {6762, MouthState::Open}, // heart (open)
    {6900},                   // (close)

    {7191, MouthState::Partial}, // con- (partial)
    {7280, MouthState::Open},    // -tro- (open)
    {7400},                      // -l (close)

    {7705, MouthState::Open},    // ca- (open)
    {7755, MouthState::Partial}, // -ff- (partial)
    {7905, MouthState::Open},    // -ei- (open)
    {8100, MouthState::Partial}, // -n- (partial)
    {8150, MouthState::Open},    // -a- (open)
    {8350},                      // -te (close)

    {8440, MouthState::Open}, // you (open)
    {8540},                   // (close)

    {8670, MouthState::Open}, // get (open)
    {8740},                   // (close)

    {8919, MouthState::Open}, // me (open)
    {9000},                   // (close)

    {9163, MouthState::Open}, // going (open)
    {9363},                   // (close)

    {10115, MouthState::Open}, // brain (open)
    {10365},                   // (close)

    {10604, MouthState::Open}, // heart (open)
    {10854},                   // (close)

    {11030, MouthState::Partial}, // con- (partial)
    {11120, MouthState::Open},    // -tro- (open)
    {11240},                      // -l (close)

    {11599, MouthState::Open},    // ca- (open) (50ms)
    {11650, MouthState::Partial}, // -ff- (partial) (150ms)
    {11800, MouthState::Open},    // -ei- (open) (105ms)
    {11905, MouthState::Partial}, // -n- (partial) (100ms)
    {12005, MouthState::Open},    // -a- (open) (200ms)
    {12205},                      // -te (close)

    {12518, MouthState::Open},    // mel- (open) (230ms)
    {12750, MouthState::Partial}, // -a- (partial) (260ms)
    {13010, MouthState::Open},    // -ton- (open) (280ms)
    {13290},                      // -in (close)

    {13518, MouthState::Open}, // love (open) (200ms)
    {13720},                   // (close)

    {13948, MouthState::Open}, // brain (open) (250ms)
    {14200},                   // (close)

    {14387, MouthState::Open}, // heart (open) (150ms)
    {14530},                   // (close)

    {15368, MouthState::Open}, // wake (open)
    {15440},                   // (close)

    {15617, MouthState::Open}, // up (open)
    {15700},                   // (close)

    {16078}, // (ss-)
    {16343}, // (-mack)
    {16844}, // (end of wiggly bit)
    {17748}, // nice
    {18028}, // to
    {18198}, // meet
    {18484}, // ya
    {19199}, // who
    {19455}, // could
    {19613}, // you
    {19970}, // be
    {21159}, // i
    {21615}, // am
    {22101}, // in-
    {22514}, // -jur-
    {22841}, // -y
    {24487}, // no
    {24685}, // you
    {24982}, // aren't
    {25695}, // you
    {25924}, // made
    {26428}, // the
    {26878}, // choice
    {27373}, // to
    {27647}, // be
    {28296}, // but
    {28592}, // i
    {28809}, // am
    {29389}, // no
    {29637}, // i
    {29896}, // am
    {30439}, // no
    {30736}, // do-
    {30927}, // -pa-
    {31044}, // -mine
    {31569}, // eh--
};

// about +-40 degrees is max angle, + is left, - is right
const std::vector<NeckEvent> neckEvents = {
    {0},              // (start forward)
    {1850, 90 + 15},  // love
    {2300, 90 - 18},  // brain
    {2850, 90 + 20},  // heart
    {3200},           // control
    {16343, 90 - 50}, // (-mack)
    {18000},
};

#endif
