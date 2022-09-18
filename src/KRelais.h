#ifndef KRELAIS_H
#define KRELAIS_H

#include <Arduino.h>
#include <KStandardCore.h>


class KRelais
{

public:
    KRelais(KStandardCore *kStandardCore);
    ~KRelais();
    void setup();
    void loop();

private:
    KStandardCore *kStandardCore;
    void mqttWrite(String digOutput, uint8_t pin);
    void mqttRead(String digOutput, uint8_t pin, uint8_t pinIndex);
    void mqttReadAll(String digOutput);


};

#endif