#include "SIGFOX.h"                         //  Include the unabiz-arduino library.
static const String device = "g88pi";       //  Set this to your device name if you're using UnaBiz Emulator.
static const bool useEmulator = false;      //  Set to true if using UnaBiz Emulator.
static const bool echo = true;              //  Set to true if the Sigfox library should display the executed commands.
static const Country country = COUNTRY_US;  //  Set this to your country to configure the Sigfox transmission frequencies.
static UnaShieldV2S transceiver(country, useEmulator, device, echo);

void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT);   
  pinMode(8, OUTPUT);
  if (!transceiver.begin()) stop(F("Unable to init Sigfox module, may be missing"));
  Serial.println("Transceiver Works");
}

int blink(){
   for (int loops = 0; loops < 3; loops++){
    digitalWrite(8, HIGH);
    delay(300);
    digitalWrite(8,LOW);
    delay(300);
   }
}

void loop() {
  while (digitalRead(6) != HIGH){
   transceiver.sendString("hello");
   blink();
   Serial.println("Message Sent");
   delay(100);
  }
}
