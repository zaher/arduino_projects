/**
*	IRRemote, read IR sensor pulses return a code of it.
*
* @license   The MIT License (MIT) Included in this distribution
*
* @ref:
*    
* @author    Zaher Dirkey <zaherdirkey at yahoo dot com>
*
*/

#define IRpin_PIN      PINB
#define IRpin          3

#define getPulse       (IRpin_PIN & _BV(IRpin))

#define IR_PULSE_COUNT 32 // max IR pulse pairs to sample
#define IR_MINPULSES 4 //min acceptable count, return code 0 if less than 4
#define IR_RESOLUTION 2 


//SONY , used Lo pulses
#define IR_DATA_LENGTH 500 //higher=1 lesser = 0
#define IR_LONG_LENGTH 2500
#define IR_LO_DATACOME 1500

//#define IR_USE_HI 0  //use high pulse instead of low for data

/*
//UNIVERSAL
#define IR_DATA_LENGTH 400
#define IR_USE_HI 1  //use high pulse instead of low for data
#define IR_LONG_LENGTH 3000
#define IR_LO_DATACOME 1500
#define IR_HI_DATACOME 4000
*/

/*
//FAN, using low bit
#define IR_DATA_LENGTH 300
#define IR_LONG_LENGTH 2500
#define IR_LO_DATACOME 0
#define IR_USE_HI 0
*/
//#define DEBUG


uint16_t maxLength = 0;
uint16_t minLength = 0;

#ifdef DEBUG
uint32_t IRTest()
{
  uint32_t code = 0;
  uint8_t count = 0; 

  while (true) {
    uint16_t pulse = 1;
    while (IRpin_PIN & _BV(IRpin)) { // got a high pulse
      pulse++;
      delayMicroseconds(IR_RESOLUTION);
    }    
    
    if (pulse > 1000)
      Serial.println("++++++++++++++++++++");
    Serial.print("HI:");
    Serial.println(pulse);

    pulse = 1;
    while (!(IRpin_PIN & _BV(IRpin))) { // got a high pulse
      pulse++;
      delayMicroseconds(IR_RESOLUTION);
    }
    Serial.print("LO:");
    Serial.println(pulse);
  }
}
#endif

uint32_t IRRead()
{  
  struct {
    bool started = false;
    uint32_t code = 0;
    uint8_t count = 0; 
    
    void reset(){
      #ifdef DEBUG
      uint16_t maxLength = 0;
      uint16_t minLength = 0;
      #endif DEBUG
      
      count = 0;
      code = 0;
    }

    void add(uint16_t pulse)
    {   
      code = code << 1;
      if (pulse > IR_DATA_LENGTH)
        code = code | 1;      
       
      #ifdef DEBUG
      if (maxLength < pulse)
        maxLength = pulse;
      if ((minLength > pulse) || (count = 0))
        minLength = pulse;
      #endif DEBUG
      count++;
    }
  } data;

/*
 * Starting loop to collect pulses 
 * First pulse it ignored, it was high, waiting forever
 * after lo pulse come usually it is long low pulse, used to sign of data comming
 * second high maybe it is a long for data comming sign too, we can ignore it, sony not need it 
 * 
 */
  data.reset();
  
  while (data.count <= IR_PULSE_COUNT)
  {
    uint16_t lo_pulse, hi_pulse;

    hi_pulse = 0;
    while (getPulse) { //Wait for ever for the first pulse
      hi_pulse++;
      delayMicroseconds(IR_RESOLUTION);      
      if ((hi_pulse >= IR_LONG_LENGTH) && (data.count > 0)) { //if it not first pulse return
        #ifdef DEBUG
        Serial.println("Long Length.");
        #endif DEBUG
        if (!data.started)
          return 0;
        else
          return data.code;
      }
    }
  
    lo_pulse = 0;
    while (!getPulse) {
      lo_pulse++;
      delayMicroseconds(IR_RESOLUTION);
    }

    if (IR_LO_DATACOME > 0)
    {
        if (!data.started) {
          data.reset();
          data.started = true;
        }
        if ((lo_pulse >= IR_LO_DATACOME))
          continue;
    }
    else {
        if (!data.started) {
          data.reset();
          data.started = true;
        }
    }
      
    
    if (data.started) {
      data.add(hi_pulse + lo_pulse);
    }
  }

#ifdef DEBUG
  Serial.println("Exit");
#endif
  return data.code;
}

void loop()
{
  //IRTest();
  //return;
  
  unsigned long code = IRRead();
#ifdef DEBUG
  if (code > 0)
  {       
    Serial.print("Code for this button: ");
    Serial.println(code);
  }
  else
    Serial.println("No code");
  Serial.println("");
#endif  
}

void setup()
{
#ifdef DEBUG
  Serial.begin(115200); // Fast IO
  Serial.setTimeout(10); // Quick read
  Serial.print("IR Reader Ready! at ");
  Serial.println(IR_DATA_LENGTH);
#endif

  pinMode(11, INPUT); // Set IR pin as input

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

