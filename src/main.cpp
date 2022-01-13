#include <ao/ao.h>
#include <atomic>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include "choice.hpp"

#define UNUSED(expr) (void)(expr)

// servos run from 400us to 2300us for 180 degrees

#ifdef __arm__
#include <pigpio.h>
#endif

// wav file always has a 44 byte header
// and we will read and play 1024 byte chunks at a time
// and we signal the track to stop playing using an atomic_bool
const std::streampos HEADER_SIZE = 0x2c;
const std::streamsize CHUNK_SIZE = 1024;
std::atomic_bool stopPlaying(false);
int audioDriverId = -1;
ao_sample_format audioFormat;
ao_device *audioDevice = nullptr;

bool initSubsystems();
bool initPwm(const unsigned pin);
void shutdownSubsystems();
void playTrack();
void processMouthEvents();
void setPwm(const unsigned pin, const int angle);

int main(void)
{
    if (!initSubsystems()) {
        shutdownSubsystems();
        return -1;
    }

    std::cout << "Starting audio thread!" << std::endl;
    std::thread audioThread(playTrack);

    std::cout << "Starting mouth thread!" << std::endl;
    std::thread mouthThread(processMouthEvents);

    audioThread.join();
    mouthThread.join();

    shutdownSubsystems();
    return 0;
}

bool initSubsystems()
{
    std::cout << "Initializing..." << std::endl;

    ao_initialize();
    audioDriverId = ao_default_driver_id();
    if (audioDriverId < 0) {
        std::cout << "[ERROR] No audio driver detected." << std::endl;
        return false;
    }
    audioFormat.bits = 8;
    audioFormat.rate = 44100;
    audioFormat.channels = 2;
    audioFormat.byte_format = AO_FMT_LITTLE;
    audioFormat.matrix = nullptr;
    audioDevice = ao_open_live(audioDriverId, &audioFormat, nullptr);
    if (audioDevice == nullptr) {
        std::cout << "[ERROR] Failed to open audio device." << std::endl;
        return false;
    }

#ifdef __arm__
    if (gpioInitialise() == PI_INIT_FAILED) {
        std::cout << "[ERROR] Failed to initialize GPIO." << std::endl;
        return false;
    }
    if (!initPwm(MOUTH_UPPER) || !initPwm(MOUTH_LOWER)) {
        std::cout << "[ERROR] Failed to initialize PWM." << std::endl;
        return false;
    }
#endif

    return true;
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

void shutdownSubsystems()
{
    std::cout << "Shutting down..." << std::endl;

    ao_close(audioDevice);
    ao_shutdown();

#ifdef __arm__
    gpioTerminate();
#endif
}

void playTrack()
{
    std::fstream file("track.wav", std::ios::in | std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        std::streamsize leftToRead = file.tellg() - HEADER_SIZE;
        char *buffer = new char[CHUNK_SIZE];
        file.seekg(HEADER_SIZE, std::ios::beg);
        std::streamsize buffSize;
        while (leftToRead > 0 && !stopPlaying.load()) {
            file.read(buffer, CHUNK_SIZE);
            buffSize = file.gcount();
            ao_play(audioDevice, buffer, buffSize);
            leftToRead -= buffSize;
        }
        delete[] buffer;
    } else {
        std::cout << "[ERROR] Failed to open audio file." << std::endl;
    }
    std::cout << "Finished playing track." << std::endl;
    stopPlaying = true;
}

void processMouthEvents()
{
    std::cout << "Total events: " << mouthEvents.size() << std::endl;
    auto event = mouthEvents.cbegin();
    auto endEvent = mouthEvents.cend();
    auto startTime = std::chrono::system_clock::now();
    while (!stopPlaying.load() && event != endEvent) {
        auto now = std::chrono::system_clock::now();
        const unsigned long ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();

        if (ms >= event->ms) {
            std::cout << "Handling event, off by " << ms - event->ms << std::endl;
            std::cout << "   ms:    " << event->ms << std::endl;
            std::cout << "   state: " << event->state << std::endl;
            setPwm(MOUTH_UPPER, event->upperAngle);
            setPwm(MOUTH_LOWER, event->lowerAngle);
            if (event->abort) {
                break;
            }
            event++;
        }
    }
    if (event->abort) {
        std::cout << "Aborting event processing." << std::endl;
        stopPlaying = true;
    } else {
        std::cout << "Processed all events." << std::endl;
    }
}

void setPwm(const unsigned pin, const int angle)
{
#ifdef __arm__
    gpioPWM(pin, ANGLE(angle));
#else
    UNUSED(pin);
    UNUSED(angle);
#endif
}
