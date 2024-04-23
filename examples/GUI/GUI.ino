#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define HomeScreen 0x0000
#define MainMenu 0x1000

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

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
