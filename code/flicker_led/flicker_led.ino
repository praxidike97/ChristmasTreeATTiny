// Needed for the perlin noise function
#include <FastLED.h>

// Pins for the LEDs
int ledPins[] = {5, 6, 7};

// Pin for the star on top
int starPin = 3;

// Offsets for the Perlin noise
int offsets[] = {0, 0, 0};
int counter = 0;
int noiseValue = 0;

void setup() {
  for (int i = 0; i < (sizeof(offsets) / sizeof(offsets[0])); i++) {
    offsets[i] = random(0, 1000);

    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(starPin, OUTPUT);
}


void loop() {
  // Star on top is always on
  digitalWrite(starPin, HIGH);
  
  for (int i = 0; i < (sizeof(offsets) / sizeof(offsets[0])); i++){
    // Hand-designed e-function to pass the value of the perlin noise through. 
    // (Why? maps the values into a range that is more sensible for the human eye)    
    int brightness = pow(2.71828, 0.03 * (inoise8(counter + offsets[i]) - 50));
    brightness = constrain(brightness, 2, 255);
    analogWrite(ledPins[i], brightness);
  }

  counter = counter + 1;

  for (int i = 0; i < (sizeof(offsets) / sizeof(offsets[0])); i++){
    // Check to make sure there is no int overflow
    if (counter + offsets[i] > 32000){
      counter = 0;
    }
  }

  delay(5);
}
