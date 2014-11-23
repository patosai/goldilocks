 /*
  *  Goldilocks
  *  WildHacks - Northwestern University
  *  Patrick Tsai, 2014
  *
  *  Modulate room temperature with nature's help!
  */

#include <SoftwareSerial.h>   //TODO need to set due to some weird wire language linker, should we absorb this whole library into smartthings
#include <SmartThings.h>
#include <Servo.h>

// ~~~ USER-DEFINED CONSTANTS HERE ~~~ //

const int PIN_THING_RX = 3;
const int PIN_THING_TX = 2;

const int SERVO_PIN = 5;     // pin to connect servo to
const int SERVO_SPEED = 120;  // 90 (no movement) - 180 (super fast)

const float GEAR_CIRC = 0.5;       // in inches
const float WINDOW_LENGTH = 24.0;   // in inches

// Enable debug?
bool enableDebug = true;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


// SmartThings object constructor
SmartThingsCallout_t messageCallout;
SmartThings smartthing(PIN_THING_RX, PIN_THING_TX, messageCallout);

Servo servo;

// Keep track of total window distance (in degrees) from close
float g_inchesMoved;

void setup()
{
  g_inchesMoved = 0.0;

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
  smartthing.run();
}

void print(String message)
{
  if (enableDebug) 
  {
    Serial.println(message); 
  }
}


