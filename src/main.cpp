#include <ao/ao.h>
#include <iostream>
#include <pigpio.h>

int main(void)
{
    std::cout << "Hiya!" << std::endl;

    ao_initialize();

    int driverId = ao_default_driver_id();
    if (driverId >= 0) {
        std::cout << "Found audio output device, id: " << driverId << std::endl;
    } else {
        std::cout << "No audio output device detected." << std::endl;
    }

    ao_shutdown();

    return 0;
}
