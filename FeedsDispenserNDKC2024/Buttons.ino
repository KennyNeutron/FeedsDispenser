#define btn_Select 5
#define btn_Up 13
#define btn_Down 12
#define btn_Cancel 14




void btn_Setup() {
  pinMode(btn_Select, INPUT_PULLUP);
  pinMode(btn_Up, INPUT_PULLUP);
  pinMode(btn_Down, INPUT_PULLUP);
  pinMode(btn_Cancel, INPUT_PULLUP);
}

void buttonPressed() {
  delay(1);
  if (Status_btn_Select() && Status_btn_Cancel() && Status_btn_Up() && Status_btn_Down()) {
    btn_pressed_toggle = false;
  }
}

bool Status_btn_Select() {
  return digitalRead(btn_Select);
}

bool Status_btn_Up() {
  return digitalRead(btn_Up);
}

bool Status_btn_Down() {
  return digitalRead(btn_Down);
}

bool Status_btn_Cancel() {
  return digitalRead(btn_Cancel);
}