#include <SoftwareSerial.h>   //TODO need to set due to some weird wire language linker, should we absorb this whole library into smartthings
#include <SmartThings.h>
#include <Servo.h>

#define PIN_THING_RX    3
#define PIN_THING_TX    2
// SmartThings object constructor
SmartThingsCallout_t messageCallout;
SmartThings smartthing(PIN_THING_RX, PIN_THING_TX, messageCallout);

Servo servo;

const int SERVO_PIN = 5;
const int SERVO_SPEED = 40;

// Keep track of total window distance (in degrees) from close
int degreesFromClose;

bool enableDebug;

void setup()
{
  enableDebug = true;
  
  degreesFromClose = 0;

  servo.attach(SERVO_PIN);
  
  smartthing.shieldSetLED(0,0,0);

  if (enableDebug)
  { // setup debug serial port
    Serial.begin(9600);         // setup serial with a baud rate of 9600
    Serial.println("Program initialized");  // print out 'setup..' on start
  }
}

void loop()
{
  // run smartthing logic
  smartthing.run();
}

void print(String message)
{
  if (enableDebug) 
  {
    Serial.println(message); 
  }
}


