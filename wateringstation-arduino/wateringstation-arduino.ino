#include <Servo.h>

Servo wateringServo;
#define moisturePin A0

const int minMoisturelevel = 100;

const int ServoPosStart = 180;
const int ServoPosWatering = 90;

int moistureLevel;

void setup() {
  pinMode(moisturePin, INPUT);
  
  Serial.begin(115200);
  
  initServo();
}

void loop() {
  measureMoistureLevel();

  if (moistureLevel < minMoisturelevel) {
    wateringSequence();
  }

  delay(200);
}

void initServo() {
  wateringServo.attach(11);
  Serial.println("Initialising Servo ...");
  wateringServo.write(ServoPosStart);
  delay(500);
  Serial.println("done");
  wateringServo.detach();
}

void measureMoistureLevel() {
  moistureLevel = analogRead(moisturePin);
  Serial.print("moisture level: ");
  Serial.println(moistureLevel);  
}

void wateringSequence() {
  wateringServo.attach(11);
  wateringServo.write(ServoPosWatering);
  delay(1500); // geef het rietje de tijd om leeg te lopen
  wateringServo.write(ServoPosStart);
  delay(1000); // geef het rietje de tijd om terug vol te lopen
  wateringServo.detach();
}

