// Opens the window a specific number of degrees
void openWindow(int degreesToTurn)
{
  // Debug lights
  smartthing.shieldSetLED(0, 0, 1);
  delay(200);
  smartthing.shieldSetLED(0, 1, 0);
  delay(200);
  smartthing.shieldSetLED(1, 0, 0);
  delay(200);
  smartthing.shieldSetLED(0, 1, 1);
  delay(200);
  smartthing.shieldSetLED(1, 1, 0);
  delay(200);
  
  smartthing.send("Shield received OPEN");        // send message to cloud
  print("Opening " + degreesToTurn);

  
  servo.write(SERVO_SPEED);
  delay(abs(degreesToTurn/SERVO_SPEED));
  servo.write(0);
  
  print("Window has been opened");

}

// Closes the window, a number of degrees
void closeWindow(int degreesToTurn)
{
  //digitalWrite(LED_PIN, LOW);   // turn LED off
  smartthing.shieldSetLED(0, 0, 0);
  smartthing.send("Shield received CLOSE");       // send message to cloud
  print("Closing " + degreesToTurn);
  
  servo.write(-SERVO_SPEED);
  delay(abs(degreesToTurn/SERVO_SPEED));
  servo.write(0);
  
  print("Window has been closed");
}

// The debug light
void debugLight()
{
  smartthing.shieldSetLED(1, 0, 0);
  delay(200);
  smartthing.shieldSetLED(0, 1, 0);
  delay(200);
  smartthing.shieldSetLED(0, 0, 1);
  delay(200);
  smartthing.shieldSetLED(1, 1, 0);
  delay(200);
  smartthing.shieldSetLED(1, 1, 1);
  delay(200);
  smartthing.shieldSetLED(1, 0, 1);
  delay(200);
  smartthing.shieldSetLED(0, 1, 1);
  delay(200);
  smartthing.shieldSetLED(3, 2, 1);
  delay(200);
  smartthing.shieldSetLED(1, 2, 3);
  delay(200);
  smartthing.shieldSetLED(2, 2, 4);
  delay(200);
  smartthing.shieldSetLED(4, 3, 1);
  delay(200);
  smartthing.shieldSetLED(0, 0, 0);  
}
