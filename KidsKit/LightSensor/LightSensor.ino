/*
 * 
 */

int pinSensor = 0;
int sensorValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  sensorValue = analogRead(pinSensor);    
  Serial.print("Value: ");
  Serial.println(sensorValue);
  delay(1000);              
}
