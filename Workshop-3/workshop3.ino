
#include <TFT_eSPI.h>
#include <DFRobot_MAX30102.h>
TFT_eSPI tft;
DFRobot_MAX30102 particleSensor;

void setup() {
  tft.init();
  tft.setRotation(3);
  tft.setTextSize(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("MAX30102", 50, 30);
  tft.drawString("HEART BEAT", 50, 70);
  tft.setTextSize(2);
  while (!particleSensor.begin()) {
    tft.drawString("MAX30102 Fail!.", 50, 120);
    delay(1000);
  }
  particleSensor.sensorConfiguration(/*ledBrightness=*/60, /*sampleAverage=*/SAMPLEAVG_4,
                                     /*ledMode=*/MODE_MULTILED, /*sampleRate=*/SAMPLERATE_100,
                                     /*pulseWidth=*/PULSEWIDTH_411, /*adcRange=*/ADCRANGE_16384);
}
int32_t SPO2;
int8_t SPO2Valid;
int32_t heartRate;
int8_t heartRateValid;

void loop() {
  particleSensor.heartrateAndOxygenSaturation(&SPO2, &SPO2Valid, &heartRate, &heartRateValid);
  tft.drawString("heartRateValid:" + String(heartRateValid), 50, 120);
  tft.drawString("heartRate:" + String(heartRate) + String("  "), 50, 150);
  tft.drawString("SPO2Valid:" + String(SPO2Valid), 50, 180);
  tft.drawString("SPO2:" + String(SPO2) + String("  "), 50, 210);
}
