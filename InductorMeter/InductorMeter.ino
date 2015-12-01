/**
   based on http://reibot.org/2011/07/19/measuring-inductance/
   http://soundation.blogspot.com/2012/07/arduino-inductance-meter.html
   pin 12 is the input to the circuit (connects to 150ohm resistor), pin 11 is the comparator/op-amp output.
*/

static int pinOut = 12;
static int pinIn = 11;
static int pinLED = 13;
static double delayPulse = 50; // original is 100
static int pulseTimeout = 10000;


double pulse, frequency, capacitance, inductance;
void setup() {
  Serial.begin(115200);
  pinMode(pinIn, INPUT);
  pinMode(pinOut, OUTPUT);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
  delay(200);
}

void loop() {
  digitalWrite(pinOut, HIGH);
  delay(5);//give some time to charge inductor.
  digitalWrite(pinOut, LOW);
  delayMicroseconds(delayPulse); //make sure resonation is measured, increase it for over 200uH inductor
  pulse = pulseIn(pinIn, HIGH, pulseTimeout); //returns 0 if timeout

  if (pulse > 0.1) { //if a timeout did not occur and it took a reading:
    capacitance = 1.79E-6; //insert capacitance here. Currently using 1uF/2uF, change it depend on your capacitors tolerance, I calebrated it
    frequency = 1.E6 / (2 * pulse);
    inductance = 1. / (capacitance * frequency * frequency * 4. * 3.14159 * 3.14159); //one of my profs told me just do squares like this
    inductance *= 1.E6; //note that this is the same as saying inductance = inductance * 1E6

    Serial.print("High for uS:");
    Serial.print( pulse );
    Serial.print("\tfrequency Hz:");
    Serial.print( frequency );
    Serial.print("\tinductance uH:");
    
    if (inductance >= 1000)
      Serial.print( inductance / 1000 );      
    else 
      Serial.print(inductance);
    Serial.println("mH" );
    digitalWrite(pinLED, HIGH);
  }
  else
  {
    Serial.println("Insert Inductor");
    digitalWrite(pinLED, LOW);
  }
  delay(200);
}


