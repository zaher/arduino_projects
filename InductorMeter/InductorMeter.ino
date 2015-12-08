/**
   based on http://reibot.org/2011/07/19/measuring-inductance/
   http://soundation.blogspot.com/2012/07/arduino-inductance-meter.html
   pin 12 is the input to the circuit (connects to 150ohm resistor), pin 11 is the comparator/op-amp output.
*/

static int pinOut = 9;
static int pinIn = 10;
static int pinLED = 13;
static double delayPulse = 100; // original is 100
static int pulseTimeout = 5000;

double pulse, frequency, inductance;
//insert capacitance here. Currently using 1uF/2uF, change it depend on your capacitors tolerance, I calebrated it
//double capacitance = 1.79E-6; 
//double capacitance = 1.03E-6; 
double capacitance = 1.00E-6; 

void setup() {
  Serial.begin(115200);
  pinMode(pinIn, INPUT);
  pinMode(pinOut, OUTPUT);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
  delay(200);
  
  digitalWrite(pinOut, HIGH);
  delay(5);//give some time to charge inductor.  
  digitalWrite(pinOut, LOW);  
}

void loop() {
  //digitalWrite(pinOut, HIGH);
  //delay(5);//give some time to charge inductor.
  //digitalWrite(pinOut, LOW);
  //delayMicroseconds(delayPulse); //make sure resonation is measured, increase it for over 200uH inductor
  pulseIn(pinIn, HIGH, pulseTimeout); 
  pulseIn(pinIn, LOW, pulseTimeout); 
  pulse = pulseIn(pinIn, HIGH, pulseTimeout); //returns 0 if timeout

  if (pulse > 0.1) { //if a timeout did not occur and it took a reading:
    frequency = 1.E6 / (2 * pulse);
    inductance = 1. / (capacitance * frequency * frequency * 4. * 3.14159 * 3.14159); //one of my profs told me just do squares like this
    inductance *= 1.E6; //note that this is the same as saying inductance = inductance * 1E6

    Serial.print("Pulse:");
    Serial.print( pulse );
    Serial.print("\tFrequency:");
    Serial.print( frequency );
    Serial.print("Hz" );
    Serial.print("\tInductance:");
    
    if (inductance >= 1000) {
      Serial.print( inductance / 1000 );      
      Serial.println("mH" );
    }      
    else {
      Serial.print(inductance);
      Serial.println("uH" );
    }
    digitalWrite(pinLED, HIGH);
  }
  else
  {
    Serial.print("Pulse:");
    Serial.print( pulse );
    Serial.println(", Insert Inductor");
    digitalWrite(pinLED, LOW);
    delay(5);
    digitalWrite(pinOut, HIGH);
    delay(5);
    digitalWrite(pinOut, LOW);      
  }
  delay(200);
}
