#include <Wire.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

const int LED_PIN = 13;
const float FREEFALL_THRESHOLD = 3.0;     // Low gravity during freefall
const float IMPACT_THRESHOLD = 20.0;      // Sudden spike on impact
const unsigned long FREEFALL_MIN_TIME = 150; // Must freefall for 150ms
const unsigned long IMPACT_TIMEOUT = 5000;   // Max time to wait for impact after freefall
const unsigned long BLINK_DURATION = 5000;

enum State {
  IDLE,           // Waiting for freefall
  IN_FREEFALL,    // Freefall detected, armed for impact
  IMPACT_DETECTED // Impact happened, blinking LED
};

State currentState = IDLE;
unsigned long freefallStartTime = 0;
unsigned long freefallConfirmedTime = 0;
unsigned long impactTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  if(!accel.begin()) {
    Serial.println("ADXL345 not detected!");
    while(1) {
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
  }
  
  accel.setRange(ADXL345_RANGE_16_G);
  
  Serial.println("ADXL345 initialized!");
  Serial.println("Waiting for freefall...");
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);
  
  // Calculate total acceleration magnitude
  float accelMagnitude = sqrt(
    event.acceleration.x * event.acceleration.x +
    event.acceleration.y * event.acceleration.y +
    event.acceleration.z * event.acceleration.z
  );
  
  unsigned long currentTime = millis();
  
  // State machine
  switch(currentState) {
    
    case IDLE:
      // Look for freefall (near-zero gravity)
      if (accelMagnitude < FREEFALL_THRESHOLD) {
        if (freefallStartTime == 0) {
          freefallStartTime = currentTime;
          Serial.print("Possible freefall... ");
          Serial.println(accelMagnitude);
        } 
        else if (currentTime - freefallStartTime >= FREEFALL_MIN_TIME) {
          // Confirmed freefall!
          currentState = IN_FREEFALL;
          freefallConfirmedTime = currentTime;
          Serial.println("*** FREEFALL CONFIRMED - ARMED FOR IMPACT ***");
        }
      } else {
        // Reset if acceleration returns
        freefallStartTime = 0;
      }
      break;
      
    case IN_FREEFALL:
      // Wait for impact spike
      if (accelMagnitude > IMPACT_THRESHOLD) {
        currentState = IMPACT_DETECTED;
        impactTime = currentTime;
        Serial.print("*** IMPACT! Magnitude: ");
        Serial.print(accelMagnitude);
        Serial.println(" m/s² ***");
      }
      // Timeout if no impact after freefall
      else if (currentTime - freefallConfirmedTime > IMPACT_TIMEOUT) {
        Serial.println("Impact timeout - resetting");
        currentState = IDLE;
        freefallStartTime = 0;
      }
      break;
      
    case IMPACT_DETECTED:
      // Blink LED
      unsigned long elapsedTime = currentTime - impactTime;
      
      if (elapsedTime < BLINK_DURATION) {
        if ((elapsedTime / 300) % 2 == 0) {
          digitalWrite(LED_PIN, HIGH);
        } else {
          digitalWrite(LED_PIN, LOW);
        }
      } else {
        // Reset everything
        digitalWrite(LED_PIN, LOW);
        currentState = IDLE;
        freefallStartTime = 0;
        Serial.println("\nReset. Waiting for next freefall...\n");
      }
      break;
  }
  
  delay(20);
}