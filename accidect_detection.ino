//first gsm will be initialized, then welcome msg will show..after getting the gps value..gpslat n long value will show..
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
static const int RXPin = 8, TXPin = 9; //(gps rx to 3 and tx to 4)
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin); //(gps rx to 3 and tx to 4)
LiquidCrystal lcd(2,3,4,5,6,7); //rd,e,d4,d5,d6,d7
int sensorPin=A0;
int sensorValue = 0;
int Switch1 = A2; //piezo
int Switch2 = A3; //start key
const int buzzer=A1;
const int motor=10;
char inChar=0;
void setup(){
Serial.begin(9600); // connect serial
ss.begin(9600); // connect serial gsm connection62
Serial.println("The GPS Received Signal:");             
   pinMode(A0,INPUT);
   pinMode(A2,INPUT_PULLUP);
   pinMode(A3,INPUT_PULLUP);
    pinMode(buzzer,OUTPUT);
     pinMode(motor,OUTPUT);
    digitalWrite(buzzer,LOW);
    digitalWrite(motor,LOW);
lcd.begin(16,2);
lcd.clear();
 lcd.setCursor(0,0);
lcd.print("GPS searching...");
lcd.setCursor(0,1);
lcd.print("Please wait...");
delay(500);
Serial.print("Project is ready to work");
 get_gps();
  delay(2000);
  lcd.clear();
  lcd.print("GPS Range Found");
  lcd.setCursor(0,1);
  lcd.print("GPS is Ready");
   Serial.println("GPS is Ready");
  delay(2000); }
  void SendLocation(char *msg)
{ 
  delay(500);
  Serial.print(msg);
  Serial.print("Copy the lat/long value and search it on google map - ");
  Serial.print(gps.location.lat(), 6);
  Serial.print(",");
  Serial.println(gps.location.lng(), 6);
  lcd.clear();
  lcd.print("Location Sent");
  delay(2000);
}
  
void loop()
{ 
 get_gps();
 if(Serial.available()>0)
  {
   
    inChar=Serial.read();
    delay(10);
    if(inChar=='#')
    {
        inChar=Serial.read();
         delay(10);
        if(inChar=='l')
        {
         
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Msg Received..");
          //digitalWrite(buzzer,HIGH);
          delay(1000);
      
        SendLocation("Car is at - ");
        
           delay(2000);
        } }    
        }
sensorValue = analogRead(sensorPin); 
  //Serial.println(sensorValue);
 if(sensorValue < 180)
  { lcd.clear();
  lcd.print("Alcohol detected");
 SendLocation("Alcohol detected - ");   
    digitalWrite(buzzer,HIGH);
   digitalWrite(motor,LOW);
      delay(30000);
   digitalWrite(buzzer,LOW);
             }
   if(!digitalRead(Switch1))
             {
              lcd.clear();
             
              lcd.print("Accident occured");
             SendLocation("Accident occured - ");
              
    digitalWrite(buzzer,HIGH);
   digitalWrite(motor,LOW);
              delay(30000);
               digitalWrite(buzzer,LOW);
   
             }
if(!digitalRead(Switch2))
             {
              lcd.clear();
             
              lcd.print("Car is running");
             SendLocation("Car starts from ");
   digitalWrite(motor,HIGH);
   delay (3000);

}}

void get_gps()

{
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LAT:");
    lcd.setCursor(4,0);
    lcd.print(gps.location.lat(), 6);
    lcd.setCursor(0,1);
    lcd.print("LON:");
    lcd.setCursor(4,1);
    lcd.print(gps.location.lng(), 6);
      
    }
  }}
