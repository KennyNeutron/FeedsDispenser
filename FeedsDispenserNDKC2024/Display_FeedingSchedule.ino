//Screen Address: 0x1200

bool display_FeedingScheduleScreen_INIT = false;

uint8_t toSched_Hour = 0;
uint8_t toSched_Minute = 0;

void display_FeedingScheduleScreen() {
  if (!display_FeedingScheduleScreen_INIT) {
    display_FeedingScheduleScreen_Setup();
  }


  u8g2.setDrawColor(2);
  u8g2.setFontPosTop();
  u8g2.setFont(u8g2_font_minicute_tr);
  u8g2.drawStr(0, 0, "Feeding Schedule");

  display_FeedingScheduleScreen_buttons();
}

void display_FeedingScheduleScreen_buttons() {

  if (!Status_btn_Cancel() && !btn_pressed_toggle) {
    btn_pressed_toggle = true;
    currentScreen = MainMenu;
  }
}

void display_FeedingScheduleScreen_Setup() {
  display_FeedingScheduleScreen_INIT = true;
}


void display_FeedingScheduleScreen_EXIT() {
  display_FeedingScheduleScreen_INIT = false;
}