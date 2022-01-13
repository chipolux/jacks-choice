#ifndef CHOICE_HPP
#define CHOICE_HPP

#include <vector>

#define ANGLE(angle) ((((2300 - 400) / 180) * angle) + 400)
#define TEMPO_MS 477

#define TOP_LIP 14
#define TOP_OPEN 165
#define TOP_CLOSE 180

#define BOT_LIP 15
#define BOT_OPEN 15
#define BOT_CLOSE 0

struct ServoEvent {
    const unsigned pin;
    const unsigned long ms;
    const int angle;
    const bool abort;

    ServoEvent(unsigned pin, unsigned long ms, int angle, bool abort = false)
        : pin(pin)
        , ms(ms)
        , angle(angle)
        , abort(abort)
    {
    }
};

const std::vector<ServoEvent> servoEvents = {
    {TOP_LIP, 0, TOP_CLOSE}, // (start closed)
    {BOT_LIP, 0, BOT_CLOSE}, // (start closed)

    {TOP_LIP, 1900, TOP_OPEN},  // love (open)
    {BOT_LIP, 1900, BOT_OPEN},  // love (open)
    {TOP_LIP, 2100, TOP_CLOSE}, // love (close)
    {BOT_LIP, 2100, BOT_CLOSE}, // love (close)

    {TOP_LIP, 2400, TOP_OPEN},  // brain (open)
    {BOT_LIP, 2400, BOT_OPEN},  // brain (open)
    {TOP_LIP, 2600, TOP_CLOSE}, // brain (close)
    {BOT_LIP, 2600, BOT_CLOSE}, // brain (close)

    {TOP_LIP, 2900, TOP_OPEN},  // heart (open)
    {BOT_LIP, 2900, BOT_OPEN},  // heart (open)
    {TOP_LIP, 3100, TOP_CLOSE}, // heart (close)
    {BOT_LIP, 3100, BOT_CLOSE}, // heart (close)

    {TOP_LIP, 3250, TOP_OPEN},      // control (open)
    {BOT_LIP, 3250, BOT_OPEN},      // control (open)
    {TOP_LIP, 3350, TOP_CLOSE - 8}, // control (open)
    {BOT_LIP, 3350, BOT_CLOSE + 8}, // control (open)
    {TOP_LIP, 3500, TOP_OPEN},      // control (open)
    {BOT_LIP, 3500, BOT_OPEN},      // control (open)
    {TOP_LIP, 3750, TOP_CLOSE},     // control (close)
    {BOT_LIP, 3750, BOT_CLOSE},     // control (close)

    {TOP_LIP, 3795, TOP_OPEN},   // caffeinate
    {TOP_LIP, 4829, TOP_CLOSE},  // melatonin
    {TOP_LIP, 5808, TOP_OPEN},   // love
    {TOP_LIP, 6762, TOP_CLOSE},  // heart
    {TOP_LIP, 7191, TOP_OPEN},   // control
    {TOP_LIP, 7705, TOP_CLOSE},  // caffeinate
    {TOP_LIP, 8456, TOP_OPEN},   // you
    {TOP_LIP, 8679, TOP_CLOSE},  // get
    {TOP_LIP, 8919, TOP_OPEN},   // me
    {TOP_LIP, 9163, TOP_CLOSE},  // going
    {TOP_LIP, 10115, TOP_OPEN},  // brain
    {TOP_LIP, 10604, TOP_CLOSE}, // heart
    {TOP_LIP, 11024, TOP_OPEN},  // control
    {TOP_LIP, 11599, TOP_CLOSE}, // caffeinate
    {TOP_LIP, 12518, TOP_OPEN},  // melatonin
    {TOP_LIP, 13518, TOP_CLOSE}, // love
    {TOP_LIP, 13948, TOP_OPEN},  // brain
    {TOP_LIP, 14387, TOP_CLOSE}, // heart
    {TOP_LIP, 15368, TOP_OPEN},  // wake
    {TOP_LIP, 15617, TOP_CLOSE}, // up
    {TOP_LIP, 16078, TOP_CLOSE}, // (ss-)
    {TOP_LIP, 16343, TOP_CLOSE}, // (-mack)
    {TOP_LIP, 16844, TOP_CLOSE}, // (end of wiggly bit)
    {TOP_LIP, 17748, TOP_OPEN},  // nice
    {TOP_LIP, 18028, TOP_CLOSE}, // to
    {TOP_LIP, 18198, TOP_OPEN},  // meet
    {TOP_LIP, 18484, TOP_CLOSE}, // ya
    {TOP_LIP, 19199, TOP_OPEN},  // who
    {TOP_LIP, 19455, TOP_CLOSE}, // could
    {TOP_LIP, 19613, TOP_OPEN},  // you
    {TOP_LIP, 19970, TOP_CLOSE}, // be
    {TOP_LIP, 21159, TOP_OPEN},  // i
    {TOP_LIP, 21615, TOP_CLOSE}, // am
    {TOP_LIP, 22101, TOP_OPEN},  // in-
    {TOP_LIP, 22514, TOP_CLOSE}, // -jur-
    {TOP_LIP, 22841, TOP_OPEN},  // -y
    {TOP_LIP, 24487, TOP_CLOSE}, // no
    {TOP_LIP, 24685, TOP_OPEN},  // you
    {TOP_LIP, 24982, TOP_CLOSE}, // aren't
    {TOP_LIP, 25695, TOP_OPEN},  // you
    {TOP_LIP, 25924, TOP_CLOSE}, // made
    {TOP_LIP, 26428, TOP_OPEN},  // the
    {TOP_LIP, 26878, TOP_CLOSE}, // choice
    {TOP_LIP, 27373, TOP_OPEN},  // to
    {TOP_LIP, 27647, TOP_CLOSE}, // be
    {TOP_LIP, 28296, TOP_OPEN},  // but
    {TOP_LIP, 28592, TOP_CLOSE}, // i
    {TOP_LIP, 28809, TOP_OPEN},  // am
    {TOP_LIP, 29389, TOP_CLOSE}, // no
    {TOP_LIP, 29637, TOP_OPEN},  // i
    {TOP_LIP, 29896, TOP_CLOSE}, // am
    {TOP_LIP, 30439, TOP_OPEN},  // no
    {TOP_LIP, 30736, TOP_CLOSE}, // do-
    {TOP_LIP, 30927, TOP_OPEN},  // -pa-
    {TOP_LIP, 31044, TOP_CLOSE}, // -mine
    {TOP_LIP, 31569, TOP_OPEN},  // eh--

    {TOP_LIP, 0, TOP_CLOSE}, // (end closed)
    {BOT_LIP, 0, BOT_CLOSE}, // (end closed)
};

#endif
