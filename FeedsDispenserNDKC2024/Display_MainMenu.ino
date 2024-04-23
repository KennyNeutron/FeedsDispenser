//Screen Address 0x1000

bool display_MainMenuScreen_INIT = false;

uint8_t menu_count = 0;

void display_MainMenuScreen() {
  if (!display_MainMenuScreen_INIT) {
    display_MainMenuScreen_Setup();
  }


  u8g2.setFontPosTop();

  u8g2.setFont(u8g2_font_minicute_tr);
  u8g2.drawStr(35, 0, "MAIN MENU");

  switch (menu_count) {
    case 0:
      u8g2.setFontMode(1);  /* activate transparent font mode */
      u8g2.setDrawColor(1); /* color 1 for the box */
      u8g2.drawBox(0, 19, 128, 16);
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_tenthinnerguys_tr);
      u8g2.drawStr(5, 20, "Clock Settings");

      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      u8g2.drawStr(5, 36, "Feeding Schedule");
      u8g2.drawStr(5, 52, "Dispense Settings");
      break;

    case 1:
      u8g2.setFontMode(1);  /* activate transparent font mode */
      u8g2.setDrawColor(1); /* color 1 for the box */
      u8g2.drawBox(0, 35, 128, 16);
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_tenthinnerguys_tr);
      u8g2.drawStr(5, 36, "Feeding Schedule");

      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      u8g2.drawStr(5, 20, "Clock Settings");
      u8g2.drawStr(5, 52, "Dispense Settings");
      break;

    case 2:
      u8g2.setFontMode(1);  /* activate transparent font mode */
      u8g2.setDrawColor(1); /* color 1 for the box */
      u8g2.drawBox(0, 51, 128, 16);
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_tenthinnerguys_tr);
      u8g2.drawStr(5, 52, "Dispense Settings");

      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      u8g2.drawStr(5, 20, "Clock Settings");
      u8g2.drawStr(5, 36, "Feeding Schedule");
      break;
    default:
      menu_count = 0;
      break;
  }

  display_MainMenuScreen_buttons();
}

void display_MainMenuScreen_buttons() {
  if (!Status_btn_Select() && !btn_pressed_toggle) {
    btn_pressed_toggle = true;
    switch (menu_count) {
      case 0:
        currentScreen = ClockSettings;
        break;

      default:
        currentScreen = HomeScreen;
        break;
    }
  }

  if (!Status_btn_Cancel() && !btn_pressed_toggle) {
    currentScreen = HomeScreen;
    btn_pressed_toggle = true;
    display_MainMenuScreen_Exit();
  }

  if (!Status_btn_Up() && !btn_pressed_toggle) {
    menu_count--;
    if (menu_count > 3) {
      menu_count = 2;
    }
    btn_pressed_toggle = true;
  }

  if (!Status_btn_Down() && !btn_pressed_toggle) {
    menu_count++;
    if (menu_count >= 3) {
      menu_count = 0;
    }
    btn_pressed_toggle = true;
  }
}


void display_MainMenuScreen_Exit() {
  display_MainMenuScreen_INIT = false;
  menu_count = 0;
}

void display_MainMenuScreen_Setup() {
  display_MainMenuScreen_INIT = true;
}