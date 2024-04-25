float WeightBeforeFeeding = 0.0;

void dispenseFeeds() {

  LoadCell_Loop();
  
  WeightBeforeFeeding = currentWeight;
  Serial.print("Weight Before Feeding:");
  Serial.println(WeightBeforeFeeding);
  while (!Actuator_FullRetract())
    ;

  Actuator_STOP();
  Serial.println("Dispensing");

  while ((WeightBeforeFeeding - currentWeight) < (toSet_FeedWeight*0.35)) {
    Serial.print("Dispensed Weight:");
    Serial.println(WeightBeforeFeeding - currentWeight);
    LoadCell_Loop();
  }

  Serial.println("EXTEND!");
  while (Status_LimitSW()) {
    Serial.print("Limit SW:");
    Serial.println(Status_LimitSW());
    Actuator_EXTEND();
    ActuatorRetract_flag = false;
  }

  Actuator_STOP();
  Serial.println("Feeding Done");

}

void getNextFeedingSchedule() {
  if (dispenseRepeat == FS_Repeat) {
    next_FeedingSchedule_Hour = FS_StartHour;
    next_FeedingSchedule_Minute = FS_StartMinute;
  }
}


bool IsItTimeToFeed() {
  if (myRTC.getHour(h12Flag, pmFlag) == next_FeedingSchedule_Hour && myRTC.getMinute() == next_FeedingSchedule_Minute) {
    return true;
  } else {
    return false;
  }
}