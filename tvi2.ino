#include <Arduino.h>
#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
#include "Vocab_US_Acorn.h"
#include "Vocab_US_TI99.h"
#include "Vocab_US_Clock.h"

Talkie voice(true, false);

const int NUM_MAPPINGS = 18;
const int SENSOR_PINS[8] = {6, 7, 8, 9, 10, 11, 12, 13};

const int num_sensors = 8;

int sensor_readings[num_sensors] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
char* interpreted_letter = "not found";

struct letter_sensor_mapping {
  char* letter;
  int sensor_readings[num_sensors];
};

// {index_tip, middle_tip, ring_tip, pinky_tip, index_joint, middle_joint, ring_joint, pinky_joint}
letter_sensor_mapping letter_sensor_mappings[NUM_MAPPINGS] = {
{"a", {0,0,0,0,0,1,1,1}},
{"d", {1,0,1,1,1,1,1,1}},
{"f", {0,1,1,1,1,1,1,1}},
{"g", {1,0,0,0,1,0,1,1}},
{"h", {1,1,0,0,1,1,0,1}},
{"i", {0,0,0,1,0,1,1,1}},
{"k/p", {1,1,0,0,1,0,1,1}},
{"l/q", {1,0,0,0,1,1,1,1}},
{"m", {0,0,0,0,1,1,1,0}},
{"n", {0,0,0,0,1,1,0,1}},
{"o", {0,0,1,1,1,1,1,1}},
{"r/u/v", {1,1,0,0,1,1,0,1}},
{"s", {0,0,0,0,1,1,1,1}},
{"t", {0,0,0,0,1,0,1,1}},
{"w", {1,1,1,1,1,1,1,0}},
{"x", {1,0,0,0,1,0,1,1}},
{"y", {0,0,0,1,1,1,1,1}}
};

void setup() {
  Serial.begin(9600);
  setupSensors();
  setupSpeakers();
}

void setupSensors() {
  for (int i = 0; i<num_sensors; i++) {
    int sensor_pin = SENSOR_PINS[i];
    pinMode(sensor_pin, INPUT_PULLUP); 
  }
}

void setupSpeakers() {
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
  updateReadings();
  updateLetter();
  speakCharacter();
  delay(1000);  
}

void updateReadings() {
  for (int i = 0; i<num_sensors; i++) {
    int sensor_pin = SENSOR_PINS[i];
    sensor_readings[i] = digitalRead(sensor_pin);
  }
}

void updateLetter() {
  for (int i = 0; i<NUM_MAPPINGS; i++) {
    boolean mapping_match = true;
    for (int j = 0; j<num_sensors; j++) {
      if (sensor_readings[j] != letter_sensor_mappings[i].sensor_readings[j]) {
        mapping_match = false;
        break;
      }
    }
    if (mapping_match) {
      interpreted_letter = letter_sensor_mappings[i].letter;
      return;  
    }
  }

  interpreted_letter = "not found";
}

void speakCharacter() {
      if (interpreted_letter == "a") {
      voice.say(spa_A);
    }
    else if (interpreted_letter == "d") {
      voice.say(spa_D);
    }
    else if (interpreted_letter == "f") {
      voice.say(spa_F);
    }
    else if (interpreted_letter == "g") {
      voice.say(spa_G);
    }
    else if (interpreted_letter == "h") {
      voice.say(spa_H);
    }
    else if (interpreted_letter == "i") {
      voice.say(spa_I);
    }
    else if (interpreted_letter == "k/p") {
      voice.say(spa_K);
      voice.say(spa_OR);
      voice.say(spa_P);
    }
    else if (interpreted_letter == "l/q") {
      voice.say(spa_L);
      voice.say(spa_OR);
      voice.say(spa_Q);
    }
    else if (interpreted_letter == "m") {
      voice.say(spa_M);
    }
    else if (interpreted_letter == "n") {
      voice.say(spa_N);
    }
    else if (interpreted_letter == "o") {
      voice.say(spa_O);
    }
    else if (interpreted_letter == "r/u/v") {
      voice.say(spa_R);
      voice.say(spa_OR);
      voice.say(spa_U);
      voice.say(spa_OR);
      voice.say(spa_V);
    }
    else if (interpreted_letter == "s") {
      voice.say(spa_S);
    }
    else if (interpreted_letter == "t") {
      voice.say(spa_T);
    }
    else if (interpreted_letter == "w") {
      voice.say(spa_W);
    }
    else if (interpreted_letter == "x") {
      voice.say(spa_X);
    }
    else if (interpreted_letter == "y") {
      voice.say(spa_Y);
    }
  Serial.print(interpreted_letter);
  Serial.print(": ");
  for (int i = 0; i<num_sensors; i++) {
    Serial.print(sensor_readings[i]);
  }
  Serial.println("");
}
