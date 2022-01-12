#ifndef CHOICE_HPP
#define CHOICE_HPP

#define TEMPO_MS 477

struct ServoEvent {
    const unsigned long ms;
    const int angle;
    const bool end;

    ServoEvent(unsigned long ms, int angle, bool end = false)
        : ms(ms)
        , angle(angle)
        , end(end)
    {
    }
};

// we must have at least one servo event in our list marked as the end
const ServoEvent servoEvents[] = {
    {1972, 180},  // love
    {2442, 0},    // brain
    {2912, 180},  // heart
    {3164, 0},    // control
    {3795, 180},  // caffeinate
    {4829, 0},    // melatonin
    {5808, 180},  // love
    {6762, 0},    // heart
    {7011, 180},  // control
    {7705, 0},    // caffeinate
    {8456, 180},  // you
    {8679, 0},    // get
    {8919, 180},  // me
    {9163, 0},    // going
    {10115, 180}, // brain
    {10604, 0},   // heart
    {10924, 180}, // control
    {11599, 0},   // caffeinate
    {12518, 180}, // melatonin
    {13518, 0},   // love
    {13948, 180}, // brain
    {14387, 0},   // heart
    {15368, 180}, // wake
    {15617, 0},   // up
    {16078, 180}, // (ss-)
    {16343, 0},   // (-mack)
    {16844, 0},   // end of wiggly bit
    {17748, 180}, // nice
    {18028, 0},   // to
    {18198, 180}, // meet
    {18484, 0},   // ya
    {19199, 180}, // who
    {19455, 0},   // could
    {19913, 180}, // you
    {19970, 0},   // be
    {21159, 180}, // i
    {21615, 0},   // am
    {22101, 180}, // in-
    {22514, 0},   // -jur-
    {22841, 180}, // -y
    {24487, 0},   // no
    {24685, 180}, // you
    {24982, 0},   // aren't
    {25695, 180}, // you
    {25924, 0},   // made
    {26428, 180}, // the
    {26878, 0},   // choice
    {27373, 180}, // to
    {27647, 0},   // be
    {28296, 180}, // but
    {28592, 0},   // i
    {28809, 180}, // am
    {29309, 0},   // no
    {29637, 180}, // i
    {29896, 0},   // am
    {30339, 180}, // no
    {30736, 0},   // do-
    {30927, 180}, // -pa-
    {31044, 0},   // -mine
    {31569, 180}, // eh--
    {0, 0, true},
};

#endif
