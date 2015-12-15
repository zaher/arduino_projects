/**
* This file is part of the "SARD"
* 
* @license   The MIT License (MIT) Included in this distribution            
* 
* @based on 
*    http://reibot.org/2011/07/19/measuring-inductance/
*    http://soundation.blogspot.com/2012/07/arduino-inductance-meter.html   
*    http://forum.allaboutcircuits.com/threads/inductor-meter-on-arduino.118518/
*    
* @author    Zaher Dirkey <zaherdirkey at yahoo dot com>
* 
*/

static int pinOut = 9; //is the comparator/op-amp output.
static int pinIn = 10; //input to the circuit (connects to 150ohm resistor)
static int pinLED = 13;
static double delayPulse = 100; // original is 100
static int pulseTimeout = 5000;

//Max of tries to before calc the average
//static int triesCount = 10.0;
static int triesCount = 1.0; //I felt it is not good idea so i will use 1 try

double pulse, avgPulse, frequency, inductance;

int tries = 0;

//insert capacitance here. Currently using 1uF/2uF, change it depend on your capacitors tolerance, I calebrated it
double capacitance = 1.035E-6;
//double capacitance = 1.00E-6;

void setup()
{
  Serial.begin(115200);
  pinMode(pinIn, INPUT);
  pinMode(pinOut, OUTPUT);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
  Serial.println("---------------------------------------------");
  Serial.println("Welcome to Inductor meter");
  Serial.println("Version: 1.1");
  Serial.println("url: https://github.com/zaher/arduino_projects/");
  Serial.println("---------------------------------------------");
  delay(200);

  avgPulse = 0;
  triggerTank();
}

void loop()
{
  pulseIn(pinIn, HIGH, pulseTimeout);
  /**
   * Now we will take the full length wave time so yes it is HIGH    
  */
  pulse = pulseIn(pinIn, LOW, pulseTimeout);
  if (pulse >= 0.1) //do not wait if timeouted
    pulse = pulse + pulseIn(pinIn, HIGH, pulseTimeout); //returns 0 if timeout

  if (pulse < 0.1) {
    Serial.print("Pulse:");
    Serial.print( pulse );
    Serial.println(", Insert Inductor");
    delay(300);
    triggerTank();
  }
  else {
    tries++;
    /*testing
    Serial.print("Try ");
    Serial.print(tries);
    Serial.print("   ");
    */
    avgPulse = avgPulse + pulse;

    if (tries >= triesCount) {
      avgPulse = avgPulse / triesCount;

      frequency = 1.E6 / avgPulse;
      inductance = 1. / (capacitance * frequency * frequency * 4. * 3.14159 * 3.14159); //one of my profs told me just do squares like this
      inductance *= 1.E6; //note that this is the same as saying inductance = inductance * 1E6

      //inductance = (avgPulse * avgPulse * 1.E6) / (capacitance *  4. * 3.14159 * 3.14159); //Thanks to Belal al Hamad

      /*
         print values
      */
      Serial.print("Pulse:");
      Serial.print( avgPulse );
      Serial.print("\tFrequency:");
      Serial.print( frequency );
      Serial.print("Hz" );
      Serial.print("\tInductance:");
      printValue(inductance);
      if (inductance >= 1000) {
        Serial.print( inductance / 1000 );
        Serial.println("mH" );
      }
      else {
        Serial.print(inductance);
        Serial.println("uH" );
      }
      digitalWrite(pinLED, HIGH);
      delay(500);

      tries = 0;
      avgPulse = 0;
    }
    else {
      Serial.print("Pulse:"); //for testing
      Serial.println( pulse );
    }
    delay(50);
  }
}

void printValue(double inductance) {
  //Code to send it to the display
}

void triggerTank() {
  digitalWrite(pinLED, LOW);
  delay(5);
  digitalWrite(pinOut, HIGH);
  delay(5);
  digitalWrite(pinOut, LOW);
  delay(5);
}
