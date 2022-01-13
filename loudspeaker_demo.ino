/*
 */

#include <Arduino.h>

#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
#include "Vocab_US_Acorn.h"
#include "Vocab_US_TI99.h"
#include "Vocab_US_Clock.h"

/*
 * Voice PWM output pins: only non inverted at pin A0
 *
 *  As default both inverted and not inverted outputs are enabled to increase volume if speaker is attached between them.
 *  Use Talkie Voice(true, false); if you only need not inverted pin or if you want to use SPI on ATmega328 which needs pin 11.
 *
 *  The outputs can drive headphones directly, or add a simple audio amplifier to drive a loudspeaker.
 */
Talkie voice(true, false);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)  || defined(ARDUINO_attiny3217)
    delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_TALKIE));

    // voice.doNotUseInvertedOutput();

#if defined(TEENSYDUINO)
        pinMode(5, OUTPUT);
        digitalWrite(5, HIGH); //Enable Amplified PROP shield
    #endif

}
void loop() {
  // Alphabet
    voice.say(spPAUSE2);
    voice.say(spa_A);
    voice.say(spa_B);
    voice.say(spa_C);
    voice.say(spa_D);
    voice.say(spa_E);
    voice.say(spa_F);
    voice.say(spa_G);
    voice.say(spa_H);
    voice.say(spa_I);
    voice.say(spa_J);
    voice.say(spa_K);
    voice.say(spa_L);
    voice.say(spa_M);
    voice.say(spa_N);
    voice.say(spa_O);
    voice.say(spa_P);
    voice.say(spa_Q);
    voice.say(spa_R);
    voice.say(spa_S);
    voice.say(spa_T);
    voice.say(spa_U);
    voice.say(spa_V);
    voice.say(spa_W);
    voice.say(spa_X);
    voice.say(spa_Y);
    voice.say(spa_Z);
  

}