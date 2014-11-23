// Turns inches into a set ms delay, depending on servo speed and gear circumference
int findDelay(float inches)
{
    float temp = abs( (inches / GEAR_CIRC) * 360 / (SERVO_SPEED-90));
    return floor(temp * 10);
}

// Opens the window a specific number of degrees
void openWindow(float inchesToOpen)
{   
  smartthing.send("Shield received OPEN");        // send message to cloud
  print("Opening");

  // if someone tries to open the window more than it can
  if (inchesToOpen > 0 && (inchesToOpen + g_inchesMoved) <= WINDOW_LENGTH)
  {
    servo.write(SERVO_SPEED);
    if (enableDebug) smartthing.shieldSetLED(0,1,0);
    
    if (inchesToOpen + g_inchesMoved >= WINDOW_LENGTH)
    {
      delay(findDelay(WINDOW_LENGTH - g_inchesMoved));
      g_inchesMoved = WINDOW_LENGTH;
    }
    else
    {
      delay(findDelay(inchesToOpen));
      g_inchesMoved += WINDOW_LENGTH;
    }
    
    if (enableDebug)smartthing.shieldSetLED(0,0,0);
    servo.write(90);
    
  }
  
  print("Window has been opened");
}

// Closes the window, a number of degrees
void closeWindow(float inchesToClose)
{  
  smartthing.send("Shield received CLOSE");       // send message to cloud
  print("Closing");
  
  // inches is guaranteed to be positive
  // if we try to close more window than is currently open
  if (inchesToClose > g_inchesMoved && g_inchesMoved > 0)
  {
     servo.write(90 - SERVO_SPEED);
     if (enableDebug) smartthing.shieldSetLED(1,0,0);
     
     if (inchesToClose > g_inchesMoved)
     {
       delay(findDelay(g_inchesMoved));
       g_inchesMoved = 0; 
     }
     else
     {
       delay(findDelay(inchesToClose));
       g_inchesMoved -= inchesToClose; 
     }
     
     if (enableDebug) smartthing.shieldSetLED(0,0,0);
     servo.write(90);

  }

  print("Window has been closed");
}
