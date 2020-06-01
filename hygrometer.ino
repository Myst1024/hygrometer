#include <FastLED.h>

#define NUM_LEDS 4
#define Water_Sensor A0 // Attach Water sensor to Arduino Digital Pin 8
#define DATA_PIN 7

// min/max LED Hue Values
int RED = 0;
int BLUE = 230;

int SENSOR_WET = 600;
int SENSOR_DRY = 23;

int currentBrightness = 50;
int sensorValue;
int normalizedValue = 0;

CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(currentBrightness);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(10,255,currentBrightness);
      FastLED.show();
    }
}

void loop() {
  sensorValue = analogRead(Water_Sensor);
  normalizedValue = normalizeWetness(sensorValue);

  Serial.println(sensorValue);
  Serial.println(normalizedValue);
  setColors(normalizedValue);
  delay(2000);                
}


void setColors(int wetness) {
  int newColor = map(wetness, 0, 100, RED, BLUE);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(newColor,255,currentBrightness);
  }
  FastLED.show();
}
/**
 * Returns wetness converted to 0-100 range
 */ 
int normalizeWetness(int wetness) {
  int constrainedValue = constrain(wetness, SENSOR_DRY, SENSOR_WET);
  return map(constrainedValue, SENSOR_DRY, SENSOR_WET, 0, 100);

}