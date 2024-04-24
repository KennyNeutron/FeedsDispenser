//Screen Address: 0x1300
bool display_DispenseSettingsScreen_INIT = false;
uint32_t DispenseSettings_LastMillis = 0;

void display_DispenseSettingsScreen() {
  if (!display_DispenseSettingsScreen_INIT) {
    display_DispenseSettingsScreen_Setup();
  }

  if (SaveSettings == true) {
    u8g2.setFont(u8g2_font_minicute_tr);
    u8g2.setFontPosTop();
    u8g2.drawStr(30, 20, "SAVING...");

    if ((millis() - DispenseSettings_LastMillis) >= 2000) {
      display_DispenseSettingsScreen_EXIT();
    }
  } else {
    u8g2.setFontMode(1); /* activate transparent font mode */
    switch (nowSetting) {
      case 0:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(30, 17, 60, 11);
        break;

      case 1:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(52, 29, 60, 11);
        break;

      case 2:
        u8g2.setDrawColor(1); /* color 1 for the box */
        u8g2.drawBox(52, 29, 60, 11);
        break;

      default:
        nowSetting = 0;
        break;
    }

    u8g2.setDrawColor(2);
    u8g2.setFontPosTop();
    u8g2.setFont(u8g2_font_minicute_tr);
    u8g2.drawStr(0, 0, "Dispense Settings");

    if (dispense_unit) {
      u8g2.drawStr(0, 18, "UNIT: Kilograms");
    } else {
      u8g2.drawStr(0, 18, "UNIT: Grams");
    }


    char ch_Weight[40] = "";
    if (dispense_unit) {
      sprintf(ch_Weight, "DISPENSE: %.1f Kg", toSet_FeedWeight);
    } else {
      sprintf(ch_Weight, "DISPENSE: %.1f g", toSet_FeedWeight);
    }
    u8g2.drawStr(0, 30, ch_Weight);

    display_DispenseSettingsScreen_buttons();
  }
}

void display_DispenseSettingsScreen_buttons() {
  if (!Status_btn_Select() && !btn_pressed_toggle) {
    nowSetting++;
    if (nowSetting >= 3) {
      nowSetting = 0;
    }
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
        dispense_unit = !dispense_unit;
        break;

      case 1:
        if (Status_btn_Up()) {
          toSet_FeedWeight += 1.0;
        } else {
          toSet_FeedWeight -= 1.0;
        }
        break;
      case 2:
        if (Status_btn_Up()) {
          toSet_FeedWeight += 0.1;
        } else {
          toSet_FeedWeight -= 0.1;
        }
        break;

      default:
        nowSetting = 0;
        break;
    }

    if (toSet_FeedWeight < 0.0) {
      toSet_FeedWeight = 0.0;
    }

    if (nowSetting == 1) {
      delay(25);
    } else {
      btn_pressed_toggle = true;
    }
  }

  if (!Status_btn_Cancel() && !btn_pressed_toggle) {
    SaveSettings = true;
    DispenseSettings_LastMillis = millis();
    btn_pressed_toggle = true;
  }
}


void display_DispenseSettingsScreen_Setup() {
  display_DispenseSettingsScreen_INIT = true;
  SaveSettings = false;
  nowSetting = 0;

  getDispenseDataFromEEPROM();
}

void display_DispenseSettingsScreen_EXIT() {

  EEPROM.write(0x05, dispense_unit);
  EEPROM.put(0x06, toSet_FeedWeight);
  EEPROM.commit();

  display_DispenseSettingsScreen_INIT = false;
  SaveSettings = false;
  currentScreen = MainMenu;
}