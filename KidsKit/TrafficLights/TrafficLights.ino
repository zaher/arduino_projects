/*
 * 
 */


void setup() {
  pinMode(13, OUTPUT);  
  digitalWrite(13, LOW); 
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(12, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(3000);              // wait for a second
  digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(11, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(10, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);              // wait for a second
}
