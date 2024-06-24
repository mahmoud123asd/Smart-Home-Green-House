//LEDS:     1 2 3 4 5 6
//Bits: 0 0 ? ? ? ? ? ? 
// Change bits values based on signal from the mobile app (1: on, 0: off)
void shift_out(char readValue)
{
  // Read value sent from mobile app (1, 2, 3, 4, 5, 6)
  //Serial.print("Value Recieved: ");
  //Serial.println(readValue);
  
  switch(readValue)
  {
    case '1':
      led1 = !led1;
      if (led1)
      {
        rec += 4;
      }
      else
      {
        rec -= 4;
      }
      break; 
    case '2':
      led2 = !led2;
      if (led2)
      {
        rec += 8;
      }
      else
      {
        rec -= 8;
      }
      break; 
    case '3':
      led3 = !led3;
      if (led3)
      {
        rec += 16;
      }
      else
      {
        rec -= 16;
      }
      break; 
    case '4':
      led4 = !led4;
      if (led4)
      {
        rec += 32;
      }
      else
      {
        rec -= 32;
      }
      break; 
    case '5':
      led5 = !led5;
      if (led5)
      {
        rec += 64;
      }
      else
      {
        rec -= 64;
      }
      break; 
    case '6':
      led6 = !led6;
      if (led6)
      {
        rec += 128;
      }
      else
      {
        rec -= 128;
      }
      break; 
  }
  digitalWrite(ld,LOW);
  shiftOut(ser,clck,MSBFIRST,rec);
  digitalWrite(ld,HIGH);
}
