#include <Arduino.h>
#include <U8g2lib.h>
#include "EEPROM.h"

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
#define FeedingSchedule 0x1200
#define DispenseSettings 0x1300

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

bool century = false;
bool h12Flag;
bool pmFlag;

uint8_t Hour = 1;
uint8_t Minute = 2;
uint8_t Second = 3;

uint16_t currentScreen = 0x0000;
bool btn_pressed_toggle = false;

//DISPENSE SETTINGS
bool dispense_unit = false;  //TRUE= Kg    FALSE= g
float toSet_FeedWeight = 0.0;

//FEEDING SCHEDULE
uint8_t FS_StartHour = 0;
uint8_t FS_StartMinute = 0;
uint8_t FS_Repeat = 1;
uint8_t FS_IntervalHour = 1;
uint8_t FS_IntervalMinute = 30;

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  u8g2.begin();
  btn_Setup();


  if (!EEPROM.begin(256)) {
    Serial.println("failed to initialise EEPROM");
  }

  // //SET-UP DATE and Time
  // myRTC.setClockMode(false);  // set to 24h
  // myRTC.setYear(24);
  // myRTC.setMonth(4);
  // myRTC.setDate(23);
  // myRTC.setDoW(3);
  // myRTC.setHour(5);
  // myRTC.setMinute(0);
  // myRTC.setSecond(0);

  getDispenseDataFromEEPROM();
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
    case 0x1200:
      display_FeedingScheduleScreen();
      break;
    case 0x1300:
      display_DispenseSettingsScreen();
      break;
    default:
      display_HomeScreen();
      break;
  }

  u8g2.sendBuffer();

  buttonPressed();
}

void getDispenseDataFromEEPROM() {
  bool wUnit = EEPROM.read(0x05);
  float f;
  EEPROM.get(0x06, f);
  dispense_unit = wUnit;
  toSet_FeedWeight = f;
  Serial.println("EEPROM DATA:");
  Serial.println(wUnit);
  Serial.println(f);
}


void getFeedingScheduleDataFromEEPROM() {
  FS_StartHour = EEPROM.read(0x10);
  FS_StartMinute = EEPROM.read(0x11);
  FS_Repeat = EEPROM.read(0x14);
  FS_IntervalHour = EEPROM.read(0x12);
  FS_IntervalMinute = EEPROM.read(0x13);
}
