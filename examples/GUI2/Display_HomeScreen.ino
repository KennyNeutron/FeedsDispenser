//Screen Address 0x0000

bool display_HomeScreen_INIT = false;

void display_HomeScreen() {
  if (!display_HomeScreen_INIT) {
    display_HomeScreen_Setup();
  }

  u8g2.setFont(u8g2_font_luBIS12_tn);

  char ch_Time[30] = "";

  sprintf(ch_Time, " %02d : %02d : %02d", Hour, Minute, Second);

  u8g2.drawStr(0, 25, ch_Time);
  display_HomeScreen_buttons();
}


void display_HomeScreen_buttons(){
  if(!Status_btn_Select()&&!btn_pressed_toggle){
    currentScreen=MainMenu;
    btn_pressed_toggle=true;
  }
}

void display_HomeScreen_Exit() {
}

void display_HomeScreen_Setup() {
  display_HomeScreen_INIT = true;
}