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
const std::streampos headerSize = 0x2c;
const std::streamsize chunkSize = 1024;
std::atomic_bool stopPlaying(false);

void playTrack();

int main(void)
{
    std::cout << "Hiya!" << std::endl;

    std::thread audioThread(playTrack);
    int i = 0;
    while (i < 10) {
        std::cout << "This is executing while the song is playing!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        i++;
    }
    stopPlaying = true;
    audioThread.join();

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
            std::streamsize leftToRead = file.tellg() - headerSize;
            char *buffer = new char[chunkSize];
            file.seekg(headerSize, std::ios::beg);

            ao_device *device = ao_open_live(driverId, &format, nullptr);
            if (device != nullptr) {
                std::streamsize buffSize;
                while (leftToRead > 0 && !stopPlaying.load()) {
                    file.read(buffer, chunkSize);
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
    ao_shutdown();
}
