
void setup() {
  Serial.begin(9600);
  Serial.println("START");
}

void loop() {
if(Serial.available()>0){
  char dt=Serial.read();
  Serial.print(dt);
}

}
