void displayReadings(void)
{
  // Send temperature, humidity, light and moisture readings to mobile app
  delay(10);
  Serial.print((int)t);
  Serial.print(";");
  Serial.print((int)h);
  Serial.print(";");
  Serial.print(light);
  Serial.print(";");
  Serial.print(moisture);
  Serial.print(";");
  Serial.println(weatherStatus);
}
