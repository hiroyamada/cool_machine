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
  // TODO: setup speaker pins  
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
  // TODO: output intepreted_character to speakers  
//  Serial.print("index_tip, middle_tip, ring_tip, pinky_tip, index_joint, middle_joint, ring_joint, pinky_joint");
//  Serial.println("");
  Serial.print(interpreted_letter);
  Serial.print(": ");
  for (int i = 0; i<num_sensors; i++) {
    Serial.print(sensor_readings[i]);
  }
  Serial.println("");
}
