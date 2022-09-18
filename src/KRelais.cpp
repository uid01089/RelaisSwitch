#include <KRelais.h>
#include <functional>

#define MQTT_WRITE_CTL_LOGIC(PIN) "/write/##PIN##"
#define MQTT_READ_CTL_LOGIC(PIN) "/read/##PIN##"
#define MQTT_READ_ALL_CTL_LOGIC "/read/all"

KRelais::KRelais(KStandardCore *kStandardCore)
{
    this->kStandardCore = kStandardCore;
}
KRelais::~KRelais() {}

void KRelais::setup()
{
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_WRITE_CTL_LOGIC(0), std::bind(&KRelais::mqttWrite, this, std::placeholders::_1, D0));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_WRITE_CTL_LOGIC(1), std::bind(&KRelais::mqttWrite, this, std::placeholders::_1, D1));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_WRITE_CTL_LOGIC(2), std::bind(&KRelais::mqttWrite, this, std::placeholders::_1, D2));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_WRITE_CTL_LOGIC(3), std::bind(&KRelais::mqttWrite, this, std::placeholders::_1, D3));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_WRITE_CTL_LOGIC(4), std::bind(&KRelais::mqttWrite, this, std::placeholders::_1, D4));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_WRITE_CTL_LOGIC(5), std::bind(&KRelais::mqttWrite, this, std::placeholders::_1, D5));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_WRITE_CTL_LOGIC(6), std::bind(&KRelais::mqttWrite, this, std::placeholders::_1, D6));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_WRITE_CTL_LOGIC(7), std::bind(&KRelais::mqttWrite, this, std::placeholders::_1, D7));

    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_READ_CTL_LOGIC(0), std::bind(&KRelais::mqttRead, this, std::placeholders::_1, D0, 0));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_READ_CTL_LOGIC(1), std::bind(&KRelais::mqttRead, this, std::placeholders::_1, D1, 1));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_READ_CTL_LOGIC(2), std::bind(&KRelais::mqttRead, this, std::placeholders::_1, D2, 2));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_READ_CTL_LOGIC(3), std::bind(&KRelais::mqttRead, this, std::placeholders::_1, D3, 3));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_READ_CTL_LOGIC(4), std::bind(&KRelais::mqttRead, this, std::placeholders::_1, D4, 4));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_READ_CTL_LOGIC(5), std::bind(&KRelais::mqttRead, this, std::placeholders::_1, D5, 5));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_READ_CTL_LOGIC(6), std::bind(&KRelais::mqttRead, this, std::placeholders::_1, D6, 6));
    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_READ_CTL_LOGIC(7), std::bind(&KRelais::mqttRead, this, std::placeholders::_1, D7, 7));

    kStandardCore->getKMqtt()->regCallBack("/" + kStandardCore->getHostname() + MQTT_READ_ALL_CTL_LOGIC, std::bind(&KRelais::mqttReadAll, this, std::placeholders::_1));

    pinMode(D0, OUTPUT);
    digitalWrite(D0, HIGH);
    pinMode(D1, OUTPUT);
    digitalWrite(D1, HIGH);
    pinMode(D2, OUTPUT);
    digitalWrite(D2, HIGH);
    pinMode(D3, OUTPUT);
    digitalWrite(D3, HIGH);
    pinMode(D4, OUTPUT);
    digitalWrite(D4, HIGH);
    pinMode(D5, OUTPUT);
    digitalWrite(D5, HIGH);
    pinMode(D6, OUTPUT);
    digitalWrite(D6, HIGH);
    pinMode(D7, OUTPUT);
    digitalWrite(D7, HIGH);
}
void KRelais::loop() {}

void KRelais::mqttWrite(String digOutput, uint8_t pin)
{
    if (digOutput == "HIGH")
    {
        digitalWrite(pin, HIGH);
    }
    else if (digOutput == "LOW")
    {
        digitalWrite(pin, LOW);
    }
}
void KRelais::mqttRead(String digOutput, uint8_t pin, uint8_t pinIndex)
{
    int status = digitalRead(pin);

    kStandardCore->getKMqtt()->publish("/" + kStandardCore->getHostname() + "/status/" + pinIndex, String(status).c_str());
}

void KRelais::mqttReadAll(String digOutput)
{
    mqttRead(digOutput, D0, 0);
    mqttRead(digOutput, D1, 1);
    mqttRead(digOutput, D2, 2);
    mqttRead(digOutput, D3, 3);
    mqttRead(digOutput, D4, 4);
    mqttRead(digOutput, D5, 5);
    mqttRead(digOutput, D6, 6);
    mqttRead(digOutput, D7, 7);
}