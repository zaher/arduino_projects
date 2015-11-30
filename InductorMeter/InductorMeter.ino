/**
 * based on http://reibot.org/2011/07/19/measuring-inductance/
 * http://soundation.blogspot.com/2012/07/arduino-inductance-meter.html
 * pin 12 is the input to the circuit (connects to 150ohm resistor), pin 11 is the comparator/op-amp output. 
*/

double pulse, frequency, capacitance, inductance;
void setup() {
  Serial.begin(115200);
  pinMode(11, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delay(200);
}

void loop() {
  digitalWrite(12, HIGH);
  delay(5);//give some time to charge inductor.
  digitalWrite(12, LOW);
  delayMicroseconds(100); //make sure resination is measured, increase it for over 200uH inductor
  pulse = pulseIn(11, HIGH, 5000); //returns 0 if timeout

  if (pulse > 0.1) { //if a timeout did not occur and it took a reading:
    capacitance = 1.79E-6; //insert capacitance here. Currently using 1uF/1uF
    frequency = 1.E6 / (2 * pulse);
    inductance = 1. / (capacitance * frequency * frequency * 4.*3.14159 * 3.14159); //one of my profs told me just do squares like this
    inductance *= 1E6; //note that this is the same as saying inductance = inductance*1E6
    if (inductance >= 1000)
    {
      Serial.print("High for uS:");
      Serial.print( pulse );
      Serial.print("\tfrequency Hz:");
      Serial.print( frequency );
      Serial.print("\tinductance mH:"); 
      Serial.println( inductance / 1000 );
      
      Serial.print("Inductance:");
      Serial.print(inductance / 1000); 
      Serial.println("mH" );  
      
    }

    else {

      Serial.print("High for uS:");
      Serial.print( pulse );
      Serial.print("\tfrequency Hz:");
      Serial.print( frequency );
      Serial.print("\tinductance uH:"); 
      Serial.println(inductance);

      Serial.print("Inductance:");
      Serial.print(inductance); 
      Serial.println("uH" );
      
      
    }
    digitalWrite(13, HIGH);    
    delay(200);
  }
  else 
  {
    Serial.println("Insert Inductor");
    digitalWrite(13, LOW);    
    delay(200);
  }
}


