// Handles all messages sent from SmartApp

void messageCallout(String message)
{
  print("Received message: " + message);

  // Check message
  if (message.toFloat() != 0)
  {
    smartthing.shieldSetLED(0,1,0);
    delay(50);
    smartthing.shieldSetLED(0,0,0);

    float inchesToMove = message.toFloat();
    if (inchesToMove > 0)
    {
      openWindow(inchesToMove); 
    }
    else
    {
      closeWindow(abs(inchesToMove)); 
    }
  }
  else if (message.equals("open"))
  {
    openWindow(WINDOW_LENGTH); 
  }
  else if (message.equals("close"))
  {
     closeWindow(WINDOW_LENGTH); 
  }
}
