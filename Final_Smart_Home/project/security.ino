void detection()
{
  if(pir1_val==HIGH)
  {
    digitalWrite(buzzer,HIGH);
  }
  else
  {
     digitalWrite(buzzer,LOW);
  }

}