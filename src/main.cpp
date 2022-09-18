#include <Arduino.h>
#include <KStandardCore.h>
#include "incredential.h"
#include <KBlink.h>
#include <KRelais.h>

// https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/

KStandardCore kStandardCore;
KRelais krelais(&kStandardCore);
KBlink kblink;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600); // Baudrate: 9600

  kStandardCore.setup("HeizungsRelaisOben", SSID, PSK, MQTT_BROKER, 1883);
  // kblink.setup(kStandardCore.getKSchedule(), 50, 3000);
  krelais.setup();
}

void loop()
{
  // put your main code here, to run repeatedly:
  kStandardCore.loop();
  // kblink.loop();
  krelais.loop();
}