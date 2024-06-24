void Tem (float Tem_c )
{
  extern int fan;
  if ((int)Tem_c>30 )
  {
    digitalWrite (fan,HIGH);
        
  }
  else
  {
    digitalWrite (fan,LOW);
  }
}
