// Handles all messages sent from SmartApp

void messageCallout(String message)
{
  // if debug is enabled print out the received message
  print("Received message: " + message);

  // if message contents equals to 'on' then call on() function
  // else if message contents equals to 'off' then call off() function
  if (message.toInt() > 0)
  {
     smartthing.shieldSetLED(0,1,0); 
  }
  else if (message.equals("open"))
  {
    openWindow(0);
  }
  else if (message.equals("close"))
  {
    closeWindow(0);
  }
  else if (message.equals("debug"))
  {
    debugLight(); 
  }
  
}
