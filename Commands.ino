// Turns inches into a set ms delay, depending on servo speed and gear circumference
int findDelay(float inches)
{
    float temp = abs( (inches / GEAR_CIRC) * 360 / (SERVO_SPEED-90));
    return floor(temp * 1000);
}

// Opens the window a specific number of degrees
void openWindow(float inchesToOpen)
{ 
  // Debug lights
  smartthing.shieldSetLED(0, 0, 1);
  delay(200);
  smartthing.shieldSetLED(0, 1, 0);
  delay(200);
  smartthing.shieldSetLED(1, 0, 0);
  delay(200);
  smartthing.shieldSetLED(1, 1, 1);
  delay(200);
  smartthing.shieldSetLED(1, 1, 0);
  delay(400);
  smartthing.shieldSetLED(0, 0, 0);
  
  smartthing.send("Shield received OPEN");        // send message to cloud
  print("Opening");

  // if someone tries to open the window more than it can
  if (inchesToOpen > 0 && (inchesToOpen + g_inchesMoved) <= WINDOW_LENGTH)
  {
    servo.write(SERVO_SPEED);
    delay(findDelay(WINDOW_LENGTH - g_inchesMoved));
    servo.write(90);
    
    g_inchesMoved = WINDOW_LENGTH;
  }
  // otherwise...
  else if (inchesToOpen > 0)
  {
    servo.write(SERVO_SPEED);
    delay(findDelay(inchesToOpen));
    servo.write(90);
    
    g_inchesMoved += inchesToOpen;
  }
  
  print("Window has been opened");
}

// Closes the window, a number of degrees
void closeWindow(float inchesToClose)
{  
  smartthing.shieldSetLED(1, 1, 1);
  delay(50);
  smartthing.shieldSetLED(0,0,0);
  
  smartthing.send("Shield received CLOSE");       // send message to cloud
  print("Closing");
  
  // inches is guaranteed to be positive
  // if we try to close more window than is currently open
  if (inchesToClose > g_inchesMoved && g_inchesMoved > 0)
  {
     servo.write(90 - SERVO_SPEED);
     delay(findDelay(g_inchesMoved));
     servo.write(90);
     
     g_inchesMoved = 0;
  }
  // for everything else
  else if (g_inchesMoved > 0)
  {
    servo.write(90 - SERVO_SPEED);
    delay(findDelay(inchesToClose));
    servo.write(90);
    
    g_inchesMoved -= inchesToClose;
  }
  
  print("Window has been closed");
}

