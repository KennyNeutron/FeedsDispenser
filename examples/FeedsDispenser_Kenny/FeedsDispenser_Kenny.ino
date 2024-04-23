uint32_t ActuatorRetract_last_millis = 0;
bool ActuatorRetract_flag = false;


void setup() {
  ActuatorSETUP();

  Serial.begin(115200);
  Serial.println("START");
  delay(2000);

  while (!Actuator_FullRetract())
    ;

  Actuator_STOP();
  delay(3000);
}

void loop() {
  while (!Status_LimitSW()) {
    Actuator_EXTEND();
    ActuatorRetract_flag = false;
  }

  Actuator_STOP();
  delay(1000);

  while (!Actuator_FullRetract())
    ;
  Actuator_STOP();
  delay(1000);
}
