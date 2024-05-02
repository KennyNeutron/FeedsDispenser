#include <Arduino.h>
#include <HX711_ADC.h>
#include <U8g2lib.h>

#include "EEPROM.h"
#include "variables.h"

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



void setup() {
  Serial.begin(9600);
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
  //myRTC.setHour(5);
  // myRTC.setMinute(0);
  // myRTC.setSecond(0);

  getDispenseDataFromEEPROM();
  getFeedingScheduleDataFromEEPROM();

  delay(500);
  Serial.println("Actuator Setup");
  ActuatorSETUP();
  delay(1000);

  Serial.println("EXTEND!");
  while (Status_LimitSW()) {
    Serial.print("Limit SW:");
    Serial.println(Status_LimitSW());
    Actuator_EXTEND();
    ActuatorRetract_flag = false;
  }
  Actuator_STOP();
  Serial.println("Actuator Setup Done");

  dispenseRepeat = FS_Repeat;

  LoadCell_Setup();
  LoadCell_Loop();
  getNextFeedingSchedule();
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

  LoadCell_Loop();


  if (IsItTimeToFeed() && !FeedingDone && currentWeight > toSet_FeedWeight) {
    Serial.println("FEED NOW!");
    dispenseFeeds();
    FeedingDone = true;
  }


  if (FeedingDone && myRTC.getMinute() != next_FeedingSchedule_Minute) {
    FeedingDone = false;
  }
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
