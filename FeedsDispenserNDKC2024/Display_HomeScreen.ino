//Screen Address 0x0000

bool display_HomeScreen_INIT = false;

uint8_t home_DOW = 1;

void display_HomeScreen() {
  if (!display_HomeScreen_INIT) {
    display_HomeScreen_Setup();
  }
  u8g2.setFontPosTop();

  u8g2.setFont(u8g2_font_luBIS12_tn);
  char ch_Time[30] = "";
  sprintf(ch_Time, " %02d : %02d : %02d", myRTC.getHour(h12Flag, pmFlag), myRTC.getMinute(), myRTC.getSecond());
  u8g2.drawStr(0, 15, ch_Time);

  u8g2.setFont(u8g2_font_minicute_tr);
  char ch_Date[30] = "";
  sprintf(ch_Date, "%02d/%02d/20%02d", myRTC.getMonth(century), myRTC.getDate(), myRTC.getYear());
  u8g2.drawStr(35, 35, ch_Date);

  display_HomeScreen_buttons();
  home_DOW = myRTC.getDoW();
  switch (home_DOW) {
    case 1:
      u8g2.drawStr(49, 50, "SUNDAY");
      break;

    case 2:
      u8g2.drawStr(49, 50, "MONDAY");
      break;

    case 3:
      u8g2.drawStr(45, 50, "TUESDAY");
      break;

    case 4:
      u8g2.drawStr(38, 50, "WEDNESDAY");
      break;

    case 5:
      u8g2.drawStr(42, 50, "THURSDAY");
      break;

    case 6:
      u8g2.drawStr(49, 50, "FRIDAY");
      break;

    case 7:
      u8g2.drawStr(41, 50, "SATURDAY");
      break;
  }
}


void display_HomeScreen_buttons() {
  if (!Status_btn_Select() && !btn_pressed_toggle) {
    currentScreen = MainMenu;
    btn_pressed_toggle = true;
  }

  if (!Status_btn_Up() && !btn_pressed_toggle) {
    Actuator_RETRACT();
  }

  if (!Status_btn_Down() && !btn_pressed_toggle && Status_LimitSW()) {
    Actuator_EXTEND();
  }

  if (Status_btn_Up() && Status_btn_Down() && !btn_pressed_toggle) {
    Actuator_STOP();
  }
}

void display_HomeScreen_Exit() {
}

void display_HomeScreen_Setup() {
  display_HomeScreen_INIT = true;
}