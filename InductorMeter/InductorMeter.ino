#include <PinChangeInterrupt.h>

/**
* This file is part of the "SARD"
*
* @license   The MIT License (MIT) Included in this distribution
*
* @based on
*    http://reibot.org/2011/07/19/measuring-inductance/
*    http://soundation.blogspot.com/2012/07/arduino-inductance-meter.html
*    http://codinglab.blogspot.be/2013/02/measuring-inductances-using-arduino.html
*    http://forum.allaboutcircuits.com/threads/inductor-meter-on-arduino.118518/
*
*
* @ref:
*    http://www.benripley.com/diy/arduino/three-ways-to-read-a-pwm-signal-with-arduino/
*    
* @author    Zaher Dirkey <zaherdirkey at yahoo dot com>
*
*/

static int pinOut = 9; //is the comparator/op-amp output.
static int pinIn = 10; //input to the circuit (connects to 150ohm resistor)
static int pinLED = 13;

double pulse, frequency, inductance;

//insert capacitance here. Currently using 1uF/2uF, change it depend on your capacitors tolerance, I calebrated it
//double capacitance = 1.035;
double capacitance = 1.00;

void setup()
{  
  Serial.begin(115200);
  pinMode(pinIn, INPUT);
  digitalWrite(pinIn, LOW);
  pinMode(pinOut, OUTPUT);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
  Serial.println("---------------------------------------------");
  Serial.println("Welcome to Inductor meter");
  Serial.println("Version: 1.1");
  Serial.println("url: https://github.com/zaher/arduino_projects/");
  Serial.println("---------------------------------------------");

  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pinIn), tick, FALLING);
  delay(200);
  
  triggerTank();
}

volatile unsigned long pluseCount = 0;

void tick()
{
  pluseCount++;
}

void loop()
{
//  pulseIn(pinIn, HIGH, pulseTimeout);
//  Now we will take the full length wave time so yes it is HIGH

  /*pulse = pulseIn(pinIn, LOW, pulseTimeout);
  if (pulse >= 0.1) //do not wait if timeouted
    pulse = pulse + pulseIn(pinIn, HIGH, pulseTimeout); //returns 0 if timeout
*/
  
  pluseCount = 0;  
  delay(1000);
  frequency = pluseCount;

  if (frequency < 10) {
    Serial.print("Frequency: ");    
    Serial.print(frequency);    
    Serial.println(", Insert Inductor");
    delay(200);
    triggerTank();
    delay(200);
  }
  else {    
    /*testing
    Serial.print("Try ");
    Serial.print(tries);
    Serial.print("   ");
    */

//      frequency = 1.E6 / avgPulse;

      inductance = (1E6 * 1E6)/ (capacitance * (frequency * frequency) * 4.0 * (PI * PI));
      //inductance = (1/ (capacitance / (avgPulse * avgPulse) * 4.0 * 3.14159 * 3.14159));
      //old one inductance = 1.E6 / (capacitance * frequency * frequency * 4. * 3.14159 * 3.14159); //one of my profs told me just do squares like this

      /*
         print values
      */
      Serial.print("Frequency: ");
      Serial.print( frequency );
      Serial.print("Hz" );
      Serial.print("\tInductance: ");
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
