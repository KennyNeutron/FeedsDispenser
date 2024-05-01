//Screen Address: 0x1200
bool display_FeedingScheduleScreen_INIT = false;
uint32_t FeedingSchedule_LastMillis = 0;

void display_FeedingScheduleScreen() {
  if (!display_FeedingScheduleScreen_INIT) {
    display_FeedingScheduleScreen_Setup();
  }

  if (SaveSettings == true) {
    u8g2.setFont(u8g2_font_minicute_tr);
    u8g2.setFontPosTop();
    u8g2.drawStr(30, 20, "SAVING...");

    if ((millis() - FeedingSchedule_LastMillis) >= 2000) {
      display_FeedingScheduleScreen_EXIT();
    }
  } else {

    u8g2.setFontMode(1); /* activate transparent font mode */
    switch (nowSetting) {
      case 0:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(62, 17, 20, 11);
        break;

      case 1:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(87, 17, 20, 11);
        break;

      case 2:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(60, 29, 20, 11);
        break;

      case 3:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(47, 41, 20, 11);
        break;

      case 4:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(72, 41, 20, 11);
        break;

      default:
        nowSetting = 0;
        break;
    }

    u8g2.setDrawColor(2);
    u8g2.setFontPosTop();
    u8g2.setFont(u8g2_font_minicute_tr);
    u8g2.drawStr(0, 0, "Feeding Schedule");

    char ch_Time[40] = "";
    sprintf(ch_Time, "Start Time: %02d : %02d", FS_StartHour, FS_StartMinute);
    u8g2.drawStr(0, 18, ch_Time);

    char ch_repeat[10] = "";
    sprintf(ch_repeat, "Repetition: %1dx", FS_Repeat);
    u8g2.drawStr(0, 30, ch_repeat);

    char ch_Interval[40] = "";
    sprintf(ch_Interval, "Interval: %02d : %02d", FS_IntervalHour, FS_IntervalMinute);
    u8g2.drawStr(0, 42, ch_Interval);

    display_FeedingScheduleScreen_buttons();
  }
}

void display_FeedingScheduleScreen_buttons() {
  if (!Status_btn_Select() && !btn_pressed_toggle) {
    nowSetting++;
    if (nowSetting >= 5) {
      nowSetting = 0;
    }
    btn_pressed_toggle = true;
  }

  if (!Status_btn_Cancel() && !btn_pressed_toggle) {
    btn_pressed_toggle = true;
    FeedingSchedule_LastMillis = millis();
    SaveSettings = true;
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
        if (btnUpDown) {
          FS_StartHour++;
        } else {
          FS_StartHour--;
        }
        break;

      case 1:
        if (btnUpDown) {
          FS_StartMinute++;
        } else {
          FS_StartMinute--;
        }
        break;

      case 2:
        if (btnUpDown) {
          FS_Repeat++;
        } else {
          FS_Repeat--;
        }
        break;

      case 3:
        if (btnUpDown) {
          FS_IntervalHour++;
        } else {
          FS_IntervalHour--;
        }
        break;

      case 4:
        if (btnUpDown) {
          FS_IntervalMinute++;
        } else {
          FS_IntervalMinute--;
        }
        break;
    }
    btn_pressed_toggle = true;
    display_FeedingScheduleScreen_VariableControl();
  }
}

void display_FeedingScheduleScreen_VariableControl() {
  if (FS_StartHour == 24) {
    FS_StartHour = 0;
  } else if (FS_StartHour > 24) {
    FS_StartHour = 23;
  }

  if (FS_StartMinute == 60) {
    FS_StartMinute = 0;
  } else if (FS_StartMinute > 60) {
    FS_StartMinute = 59;
  }

  if (FS_Repeat >= 7) {
    FS_Repeat = 1;
  } else if (FS_Repeat == 0) {
    FS_Repeat = 6;
  }

  if (FS_IntervalHour == 24) {
    FS_IntervalHour = 0;
  } else if (FS_IntervalHour > 24) {
    FS_IntervalHour = 23;
  }

  if (FS_IntervalMinute == 60) {
    FS_IntervalMinute = 0;
  } else if (FS_IntervalMinute > 60) {
    FS_IntervalMinute = 59;
  }
}

void display_FeedingScheduleScreen_Setup() {
  display_FeedingScheduleScreen_INIT = true;
  SaveSettings = false;
  dispenseRepeat = FS_Repeat;
  getFeedingScheduleDataFromEEPROM();
}


void display_FeedingScheduleScreen_EXIT() {
  display_FeedingScheduleScreen_INIT = false;
  SaveSettings = false;

  EEPROM.write(0x10, FS_StartHour);
  EEPROM.write(0x11, FS_StartMinute);
  EEPROM.write(0x12, FS_IntervalHour);
  EEPROM.write(0x13, FS_IntervalMinute);
  EEPROM.write(0x14, FS_Repeat);
  EEPROM.commit();
  
  currentScreen = MainMenu;
}