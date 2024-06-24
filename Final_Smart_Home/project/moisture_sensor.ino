void MoistureSensor(void)
{
  // Control Water Pump
  
   if (moisture > 700)
  {
   digitalWrite(waterPump, HIGH);
  }
  else
  {
    digitalWrite(waterPump, LOW);
  }
}
 