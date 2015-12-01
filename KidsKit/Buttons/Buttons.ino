/*
 * 
 */

int pinValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  pinValue = digitalRead(3);    
  Serial.print("Value: ");
  Serial.println(pinValue);
  delay(500);              
}
