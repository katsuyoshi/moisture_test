#include <Arduino.h>
#include <M5Stack.h>

#define OUT_PIN       2
#define SEN_SEL_PIN   17
#define AD_PIN        35

#define SEN_COUNT     2
#define AVR_COUNT     10

#define INTERVAL      100

int moisture_values[SEN_COUNT] = { 0 };

void setup() {
  M5.begin();
  Serial.begin(115200);

  pinMode(OUT_PIN, OUTPUT);
  pinMode(OUT_PIN, OUTPUT);
  pinMode(SEN_SEL_PIN, OUTPUT);
  digitalWrite(SEN_SEL_PIN, LOW);

  M5.Lcd.setTextSize(4);
  M5.Lcd.setTextColor(WHITE);
}

void loop() {
  int val;
  
  for (int ch = 0; ch < SEN_COUNT; ch++) {
    val = 0;
    
    Serial.printf("---- ch%d \n", ch);

    // switch sensor
    digitalWrite(SEN_SEL_PIN, ch == 0 ? LOW : HIGH);
    delay(INTERVAL);
    
    for (int i = 0; i < AVR_COUNT; i++) {
      {
        digitalWrite(OUT_PIN, HIGH);
        delay(INTERVAL);
        val += analogRead(AD_PIN);
      }

      {
        digitalWrite(OUT_PIN, LOW);
        delay(INTERVAL);
      }
    }
    val /= AVR_COUNT;
    moisture_values[ch] = val;
    Serial.printf("val: %d\n", val);
  }

  M5.Lcd.clear(BLACK);
  M5.Lcd.setCursor(0, 0);
  for (int ch = 0; ch < SEN_COUNT; ch++) {
    M5.Lcd.printf("CH%d: %8d\n", ch, moisture_values[ch]);
  }
}
