void rain (void)
{
  // 1 --> bright weather
  // 0 --> rainy weather
  if (rain_value<=512)
  {
    //app
    weatherStatus = 0;
  }
  else if (rain_value>512)
  {
    //app
    weatherStatus = 1;
  }
}
