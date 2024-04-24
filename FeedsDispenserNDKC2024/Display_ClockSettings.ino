//Screen Address: 0x1100
bool display_ClockSettings_INIT = false;

bool ClockSettingsUpdateMode = false;  //False= MANUAL   True= AUTO (Via Internet)

uint8_t toSet_Hour = 0;
uint8_t toSet_Minute = 0;
uint8_t toSet_Second = 0;
uint8_t toSet_Month = 0;
uint8_t toSet_Date = 0;
uint8_t toSet_Year = 0;
uint8_t toSet_DOW = 0;

uint8_t nowSetting = 0;

bool SaveSettings = false;

uint32_t ClockSettings_LastMillis = 0;

bool ClockSettings_Saved = false;

void display_ClockSettingsScreen() {
  if (!display_ClockSettings_INIT) {
    display_ClockSettingsScreen_Setup();
  }

  if (SaveSettings == true) {
    u8g2.setFont(u8g2_font_minicute_tr);
    u8g2.setFontPosTop();
    u8g2.drawStr(30, 20, "SAVING...");

    if (!ClockSettings_Saved) {
      //SET-UP DATE and Time
      myRTC.setClockMode(false);  // set to 24h
      myRTC.setYear(toSet_Year);
      myRTC.setMonth(toSet_Month);
      myRTC.setDate(toSet_Date);
      myRTC.setDoW(toSet_DOW);
      myRTC.setHour(toSet_Hour);
      myRTC.setMinute(toSet_Minute);
      myRTC.setSecond(toSet_Second);
      ClockSettings_Saved=true;
    }

    if ((millis() - ClockSettings_LastMillis) >= 2000) {
      display_ClockSettingsScreen_EXIT();
    }

  } else {
    u8g2.setFontMode(1); /* activate transparent font mode */

    switch (nowSetting) {
      case 0:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(42, 17, 60, 11);
        break;

      case 1:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(27, 29, 20, 11);
        break;

      case 2:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(52, 29, 20, 11);
        break;

      case 3:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(77, 29, 20, 11);
        break;

      case 4:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(28, 42, 20, 11);
        break;

      case 5:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(56, 42, 20, 11);
        break;

      case 6:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(81, 42, 20, 11);
        break;

      case 7:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(24, 53, 80, 15);
        break;

      default:
        nowSetting = 0;
        break;
    }

    u8g2.setDrawColor(2);
    u8g2.setFontPosTop();
    u8g2.setFont(u8g2_font_minicute_tr);
    u8g2.drawStr(0, 0, "Clock Settings");

    if (ClockSettingsUpdateMode) {
      u8g2.drawStr(0, 18, "Update: AUTOMATIC");
    } else {
      u8g2.drawStr(0, 18, "Update: MANUAL");
    }


    char ch_Time[40] = "";
    sprintf(ch_Time, "TIME: %02d : %02d : %02d", toSet_Hour, toSet_Minute, toSet_Second);
    u8g2.drawStr(0, 30, ch_Time);

    char ch_Date[40] = "";
    sprintf(ch_Date, "DATE: %02d / %02d / %02d", toSet_Month, toSet_Date, toSet_Year);
    u8g2.drawStr(0, 42, ch_Date);

    switch (toSet_DOW) {
      case 1:
        u8g2.drawStr(0, 54, "DAY: SUNDAY");
        break;
      case 2:
        u8g2.drawStr(0, 54, "DAY: MONDAY");
        break;
      case 3:
        u8g2.drawStr(0, 54, "DAY: TUESDAY");
        break;
      case 4:
        u8g2.drawStr(0, 54, "DAY: WEDNESDAY");
        break;
      case 5:
        u8g2.drawStr(0, 54, "DAY: THURSDAY");
        break;
      case 6:
        u8g2.drawStr(0, 54, "DAY: FRIDAY");
        break;
      case 7:
        u8g2.drawStr(0, 54, "DAY: SATURDAY");
        break;
    }

    display_ClockSettingsScreen_buttons();
  }
}

void display_ClockSettingsScreen_buttons() {
  if (!Status_btn_Select() && !btn_pressed_toggle) {
    nowSetting++;
    if (nowSetting >= 8) {
      nowSetting = 0;
    }
    btn_pressed_toggle = true;
  }

  if (!Status_btn_Cancel() && !btn_pressed_toggle) {
    SaveSettings = true;
    ClockSettings_LastMillis = millis();
    btn_pressed_toggle = true;
  }

  if ((!Status_btn_Up() || !Status_btn_Down()) && !btn_pressed_toggle) {
    bool btnUpDown = false;  //true:UP   false:DOWN
    if (Status_btn_Up()) {
      btnUpDown = false;
    } else {
      btnUpDown = true;
    }

    switch (nowSetting) {
      case 0:
        ClockSettingsUpdateMode = !ClockSettingsUpdateMode;
        break;

      case 1:
        if (btnUpDown) {
          toSet_Hour++;
        } else {
          toSet_Hour--;
        }
        break;

      case 2:
        if (btnUpDown) {
          toSet_Minute++;
        } else {
          toSet_Minute--;
        }
        break;

      case 3:
        if (btnUpDown) {
          toSet_Second++;
        } else {
          toSet_Second--;
        }
        break;

      case 4:
        if (btnUpDown) {
          toSet_Month++;
        } else {
          toSet_Month--;
        }
        break;

      case 5:
        if (btnUpDown) {
          toSet_Date++;
        } else {
          toSet_Date--;
        }
        break;

      case 6:
        if (btnUpDown) {
          toSet_Year++;
        } else {
          toSet_Year--;
        }
        break;

      case 7:
        if (btnUpDown) {
          toSet_DOW++;
        } else {
          toSet_DOW--;
        }
        break;

      default:
        nowSetting = 0;
        break;
    }
    display_ClockSettingsScreen_VariableControl();

    btn_pressed_toggle = true;
  }
}

void display_ClockSettingsScreen_VariableControl() {
  if (toSet_Hour == 24) {
    toSet_Hour = 0;
  } else if (toSet_Hour > 24) {
    toSet_Hour = 23;
  }

  if (toSet_Minute == 60) {
    toSet_Minute = 0;
  } else if (toSet_Minute > 60) {
    toSet_Minute = 59;
  }

  if (toSet_Second == 60) {
    toSet_Second = 0;
  } else if (toSet_Second > 60) {
    toSet_Second = 59;
  }

  if (toSet_Month == 13) {
    toSet_Month = 1;
  } else if (toSet_Month > 13) {
    toSet_Month = 12;
  }

  if (toSet_Date == 32) {
    toSet_Date = 1;
  } else if (toSet_Date > 32) {
    toSet_Date = 31;
  }

  if (toSet_Year == 100) {
    toSet_Year = 0;
  } else if (toSet_Year > 100) {
    toSet_Year = 99;
  }

  if (toSet_DOW >= 8) {
    toSet_DOW = 1;
  } else if (toSet_DOW == 0) {
    toSet_DOW = 7;
  }
}

void display_ClockSettingsScreen_Setup() {
  toSet_Hour = myRTC.getHour(h12Flag, pmFlag);
  toSet_Minute = myRTC.getMinute();
  toSet_Second = myRTC.getSecond();

  toSet_Month = myRTC.getMonth(century);
  toSet_Date = myRTC.getDate();
  toSet_Year = myRTC.getYear();

  toSet_DOW = myRTC.getDoW();

  SaveSettings = false;

  ClockSettings_Saved = false;

  display_ClockSettings_INIT = true;
}

void display_ClockSettingsScreen_EXIT() {
  nowSetting=0;
  SaveSettings = false;
  display_ClockSettings_INIT = false;
  currentScreen = MainMenu;
}