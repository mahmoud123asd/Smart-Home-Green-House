/******************** Includes section start *******************/
#include <dht.h>
#include <Keypad_I2C.h>
#include <Keypad.h>  // GDY120705
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Servo.h"
#include "temp.h"
/******************** Includes section End ********************/

/******************** Macro section start *******************/
#define I2CADDR 0x21
#define clck 12
#define ld 10
#define ser 8
#define servo_pin 3
/******************** Macro section End *******************/

/******************** Global variables section start *******************/
// Refresh readings on app every 10 seconds
unsigned long startMillis;
unsigned long currentMillis;
unsigned long period = 1000;
// LED System
bool led1 = false;
bool led2 = false;
bool led3 = false;
bool led4 = false;
bool led5 = false;
bool led6 = false;
byte rec; // Changes based on serial values sent via mobile app
// security
bool security = false;
int pir1=9;
int buzzer=11;
int pir1_val;
// rain sensor
int rain_pin =A3;
int rain_value;
int weatherStatus;
//garage system
int ir1_pin = 4;
int ir2_pin =6;
int ir1_value;
int ir2_value;
bool carInside = false;
bool carOutside = false;
// temp system
float Tem_c;
int fan=13;
//green house system
float t;
float h;
int light;
int moisture;
int dht_sensor = 5;
int moistureSensor = A0;
int LDR = A1;
int waterPump = 2;
//door system
char Key;
int counter = 0;
String c_pass = "1234";
String pass;
const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 0, 1, 2, 3 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 4, 5, 6, 7 };  //connect to the column pinouts of the keypad

/******************** Global variables section End ********************/

/******************** structure section start *******************/
Keypad_I2C customKeypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR);
LiquidCrystal_I2C lcd2(0x27, 16, 2);
Servo myservo;
Servo servo_ir;
dht d;
/******************** strcuture section End ********************/

void setup() 
{
   Wire.begin();          // GDY200622
  customKeypad.begin();  // GDY120705
  startMillis = millis();
  Serial.begin(9600);
    // initialize the lcd
  lcd2.init();
  lcd2.backlight();
  //shift reg
  pinMode(ld, OUTPUT);
  pinMode(clck, OUTPUT);
  pinMode(ser, OUTPUT);
  //door
  myservo.attach(servo_pin);
   myservo.write(0);
  //garge
   servo_ir.attach(7);
   servo_ir.write(0);
   pinMode(ir1_pin,INPUT);
   pinMode(ir2_pin,INPUT);
   //temp 
  pinMode(fan, OUTPUT);
  // security
    pinMode(pir1, INPUT);
     pinMode(buzzer, OUTPUT);
    //rain
    pinMode(rain_pin,INPUT);
    // green house
    pinMode(waterPump,OUTPUT);
}

void loop()
{
   /*door system*/
   Key = customKeypad.getKey();
    lcd2.setCursor(0, 0);
    lcd2.print("enter password");
    if (Key != NO_KEY && Key != '#')
     {
      pass += Key;
      counter++;
      lcd2.setCursor(counter, 1);
      lcd2.print("*");
    } 
    else if (Key == '#') 
    {
      if (pass == c_pass) 
      {
        lcd2.clear();
        lcd2.setCursor(0, 0);
        lcd2.print("door is open ");
         //open door
        myservo.write(180);
         delay(1000);
        counter = 0;
        //close door
          myservo.write(0);
      } 
      else 
      {
        lcd2.clear();
        lcd2.setCursor(0, 0);
        lcd2.print("door is closed ");
         myservo.write(0);
         delay(1000);
        counter = 0;
      }
      pass = "";
    }


  currentMillis = millis(); 
  // Mobile app
  if (Serial.available() > 0)
  {
    char readValue = Serial.read();
   
     if (readValue == 's')
    {
      security = !security; 
    }
    else
    {
      //lighting system
      shift_out(readValue);
    }
  }
    
  // Green House Readings
  d.read11(dht_sensor);
  h = d.humidity;
  t = d.temperature;
  moisture = analogRead(moistureSensor);
  light = analogRead(LDR);
  MoistureSensor();
  /*security*/
  if (security)
  {
    pir1_val=digitalRead(pir1);
    detection();
  }
  // Testing Led System With Serial
  // Serial.print("rec: ");
  // Serial.println(rec);
  /*garge system*/
  ir1_value=digitalRead(ir1_pin);
  ir2_value=digitalRead(ir2_pin);
  if (ir1_value==0 && carInside == false)
  {
    servo_ir.write(180);
  }
  else if(ir2_value==0 && carInside == false)
  {
    servo_ir.write(0);
    carInside = true;
  }
  else if(ir1_value == 1 && ir2_value == 1 && carInside == true)
  {
    servo_ir.write(180);
  }
  else if(ir1_value == 0 && carInside == true)
  {
    carOutside = true;
  }
  if (ir1_value == 1 && ir2_value == 1 && carInside == true && carOutside == true)
  {
    carInside = false;
    carOutside = false;
    servo_ir.write(0);
  }
  /*rain detection*/
  rain_value=analogRead(rain_pin);
  rain();
  /*temp system*/
  Tem(t);
  // Displaying readings on the mobile app
  if ((currentMillis - startMillis) > period)
  {
    displayReadings();
    startMillis = currentMillis;
  }
}
