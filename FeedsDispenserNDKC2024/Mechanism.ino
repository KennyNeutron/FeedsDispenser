float WeightBeforeFeeding = 0.0;

void dispenseFeeds() {
  u8g2.clearBuffer();

  u8g2.drawStr(30, 20, "DISPENSING...");
  u8g2.sendBuffer();
  LoadCell_Loop();

  WeightBeforeFeeding = currentWeight;
  Serial.print("Weight Before Feeding:");
  Serial.println(WeightBeforeFeeding);
  while (!Actuator_FullRetract())
    ;

  Actuator_STOP();
  Serial.println("Dispensing");

  while ((WeightBeforeFeeding - currentWeight) < (toSet_FeedWeight * 0.35)) {
    Serial.print("Dispensed Weight:");
    LoadCell_Loop();
    char ch_CurrentWeight[15] = "";
    sprintf(ch_CurrentWeight, "CW: %.1f", currentWeight);
    u8g2.drawStr(0, 0, ch_CurrentWeight);
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
  dispenseRepeat--;
  getNextFeedingSchedule();
}


void getNextFeedingSchedule() {
  if (dispenseRepeat == FS_Repeat) {
    next_FeedingSchedule_Hour = FS_StartHour;
    next_FeedingSchedule_Minute = FS_StartMinute;
  } else {
    next_FeedingSchedule_Minute = next_FeedingSchedule_Minute + FS_IntervalMinute;
    if (next_FeedingSchedule_Minute >= 60) {
      next_FeedingSchedule_Minute = next_FeedingSchedule_Minute - 60;
      next_FeedingSchedule_Hour++;
    }
    next_FeedingSchedule_Hour = next_FeedingSchedule_Hour + FS_IntervalHour;
    if (dispenseRepeat == 0) {
      dispenseRepeat == FS_Repeat;
      next_FeedingSchedule_Hour = FS_StartHour;
      next_FeedingSchedule_Minute = FS_StartMinute;
    }
  }

  if (next_FeedingSchedule_Hour >= 24) {
    dispenseRepeat == FS_Repeat;
  }
}


bool IsItTimeToFeed() {
  if (myRTC.getHour(h12Flag, pmFlag) == next_FeedingSchedule_Hour && myRTC.getMinute() == next_FeedingSchedule_Minute) {
    return true;
  } else {
    return false;
  }
}