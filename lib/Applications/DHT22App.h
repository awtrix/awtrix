#ifndef AwtrixDHT22Application_h
#define AwtrixDHT22Application_h

#include <IApplication.h>
#include "DHT.h"

#define SENSOR_PIN 9

class DHT22App : public IApplication
{
    private:
        DHT dht;
        unsigned long elapsed = 0;
    public:
        void render(DisplayManager&) override;
        void tick(unsigned long) override;
        void enable() override;
};

#endif