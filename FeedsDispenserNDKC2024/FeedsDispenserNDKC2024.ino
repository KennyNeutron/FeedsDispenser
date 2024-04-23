#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include <DS3231.h>

DS3231 myRTC;


#define HomeScreen 0x0000
#define MainMenu 0x1000
#define ClockSettings 0x1100

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

bool century = false;
bool h12Flag;
bool pmFlag;

uint8_t Hour = 1;
uint8_t Minute = 2;
uint8_t Second = 3;

uint16_t currentScreen = 0x0000;
bool btn_pressed_toggle = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  u8g2.begin();
  btn_Setup();

  // //SET-UP DATE and Time
  // myRTC.setClockMode(false);  // set to 24h
  // myRTC.setYear(24);
  // myRTC.setMonth(4);
  // myRTC.setDate(23);
  // myRTC.setDoW(3);
  // myRTC.setHour(5);
  // myRTC.setMinute(0);
  // myRTC.setSecond(0);
}

void loop() {
  u8g2.clearBuffer();

  switch (currentScreen) {
    case 0x0000:
      display_HomeScreen();
      break;
    case 0x1000:
      display_MainMenuScreen();
      break;
    case 0x1100:
      display_ClockSettingsScreen();
      break;
    default:
      display_HomeScreen();
      break;
  }

  u8g2.sendBuffer();

  // Serial.println("STATUS SELECT:" + String(Status_btn_Select()));
  // Serial.println("STATUS UP:" + String(Status_btn_Up()));
  // Serial.println("STATUS DOWN:" + String(Status_btn_Down()));
  // Serial.println("STATUS CANCEL:" + String(Status_btn_Cancel()));
  buttonPressed();
}
