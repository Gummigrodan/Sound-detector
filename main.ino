#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    8
#define TFT_DC     9
#define SOUND_PIN  A0

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

int xPos = 0;
int lastValue = 0;

void setup() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  delay(100);                      
  lastValue = analogRead(SOUND_PIN); 
}

void loop() {

  int soundValue = analogRead(SOUND_PIN);
  int delta = abs(soundValue - lastValue);

  int waveHeight = map(delta, 0, 30, 0, 60);
  waveHeight = constrain(waveHeight, 0, 60);

  int centerY = 64;

  tft.drawFastVLine(xPos, 0, 128, ST77XX_BLACK);

  tft.drawFastVLine(xPos, centerY - waveHeight/2,
                    waveHeight, ST77XX_GREEN);

  lastValue = soundValue;

  xPos++;
  if (xPos >= 160) {
    xPos = 0;
  }

  delay(15);
}