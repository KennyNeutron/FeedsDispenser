#define Actuator_Enable 23
#define Actuator_IN1 32
#define Actuator_IN2 33
#define Actuator_LimitSW 25


bool Actuator_FullRetract() {
  if (!ActuatorRetract_flag) {
    Actuator_RETRACT();
    ActuatorRetract_last_millis = millis();
    ActuatorRetract_flag = true;
    Serial.println("last millis saved");
  }

  if (ActuatorRetract_flag && (millis() - ActuatorRetract_last_millis) >= 9000) {
    return true;
  } else {
    return false;
  }
}

void ActuatorSETUP() {
  pinMode(Actuator_Enable, OUTPUT);
  pinMode(Actuator_IN1, OUTPUT);
  pinMode(Actuator_IN2, OUTPUT);
  pinMode(Actuator_LimitSW, INPUT_PULLUP);
}

void Actuator_EXTEND() {
  Serial.println("Actuator EXTEND!");
  digitalWrite(Actuator_Enable, 1);
  digitalWrite(Actuator_IN1, 0);
  digitalWrite(Actuator_IN2, 1);
}

void Actuator_RETRACT() {
  Serial.println("Actuator RETRACT!");
  digitalWrite(Actuator_Enable, 1);
  digitalWrite(Actuator_IN1, 1);
  digitalWrite(Actuator_IN2, 0);
}

void Actuator_STOP() {
  Serial.println("Actuator STOP!");
  digitalWrite(Actuator_Enable, 0);
  digitalWrite(Actuator_IN1, 0);
  digitalWrite(Actuator_IN2, 0);
}

bool Status_LimitSW() {
  if (!digitalRead(Actuator_LimitSW)) {
    return true;
  } else if (digitalRead(Actuator_LimitSW)) {
    return false;
  } else {
    return true;
  }
  return true;
}