#include <ao/ao.h>
#include <atomic>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#ifdef __arm__
#include <pigpio.h>
#endif

// wav file always has a 44 byte header
// and we will read and play 1024 byte chunks at a time
// and we signal the track to stop playing using an atomic_bool
const std::streampos HEADER_SIZE = 0x2c;
const std::streamsize CHUNK_SIZE = 1024;
std::atomic_bool STOP_PLAYING(false);

const unsigned PWM_PIN = 14;

void playTrack();

int main(void)
{
    std::cout << "Starting audio thread!" << std::endl;
    std::thread audioThread(playTrack);

    std::cout << "Initializing GPIO!" << std::endl;
    if (gpioInitialise() > 0) {
        gpioSetMode(PWM_PIN, PI_OUTPUT);
        gpioSetPWMfrequency(PWM_PIN, 50);
        gpioSetPWMrange(PWM_PIN, 1e6 / 50);

        int i = 0;
        while (!STOP_PLAYING.load() && i < 30) {
            std::cout << "Cycling servo: " << i << std::endl;
            gpioPWM(PWM_PIN, 400);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            gpioPWM(PWM_PIN, 2300);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            i++;
        }
    } else {
        std::cout << "[ERROR] Failed to initialize GPIO." << std::endl;
    }

    STOP_PLAYING = true;
    audioThread.join();
    gpioTerminate();
    return 0;
}

void playTrack()
{
    ao_initialize();
    int driverId = ao_default_driver_id();
    if (driverId >= 0) {
        ao_sample_format format;
        format.bits = 8;
        format.rate = 44100;
        format.channels = 2;
        format.byte_format = AO_FMT_LITTLE;
        format.matrix = nullptr;

        std::fstream file("track.wav", std::ios::in | std::ios::binary | std::ios::ate);
        if (file.is_open()) {
            std::streamsize leftToRead = file.tellg() - HEADER_SIZE;
            char *buffer = new char[CHUNK_SIZE];
            file.seekg(HEADER_SIZE, std::ios::beg);

            ao_device *device = ao_open_live(driverId, &format, nullptr);
            if (device != nullptr) {
                std::streamsize buffSize;
                while (leftToRead > 0 && !STOP_PLAYING.load()) {
                    file.read(buffer, CHUNK_SIZE);
                    buffSize = file.gcount();
                    ao_play(device, buffer, buffSize);
                    leftToRead -= buffSize;
                }
                ao_close(device);
            } else {
                std::cout << "[ERROR] Failed to open audio device." << std::endl;
            }

            delete[] buffer;
        } else {
            std::cout << "[ERROR] Failed to open audio file." << std::endl;
        }
    } else {
        std::cout << "[ERROR] No audio output device detected." << std::endl;
    }
    STOP_PLAYING = true;
    ao_shutdown();
}
