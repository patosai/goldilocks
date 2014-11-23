// Handles all messages sent from SmartApp

void messageCallout(String message)
{
  print("Received message: " + message);

  // Check message
  if (message.toFloat() != 0)
  {
    smartthing.shieldSetLED(0,1,0); 

    float inchesToMove = message.toFloat();
    if (abs(inchesToMove) > 0)
    {
      openWindow(inchesToMove); 
    }
    else
    {
      closeWindow(inchesToMove); 
    }
  }
}
