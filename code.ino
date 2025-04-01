#define BLYNK_TEMPLATE_ID "TMPL3VEBNA-WR"
#define BLYNK_TEMPLATE_NAME "WATERMANAGE"
#define BLYNK_AUTH_TOKEN "RCggJswGq9RFoiWbG6HhP1j2SO-GaWjK"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "IOT";
char pass[] = "12345678";
BlynkTimer timer;
#define Relay D0
#define soil D1
#define leak D2

void setup()
{
  Serial.begin(9600);
  pinMode(Relay, OUTPUT);
  pinMode(soil, INPUT);
  pinMode(leak, INPUT);
  digitalWrite(Relay,LOW);
  Serial.println("initialisation is done ");
  delay(100);
  Blynk.begin(auth, ssid, pass);
  Serial.println("connected ");   
  timer.setInterval(500,sensorupdate);      
}
void sensorupdate()
{
  int f=digitalRead(soil);
  int g=digitalRead(leak);
  Serial.println("the soil value is : "+String(f));
  Serial.println("the leak value is : "+String(g));
  if(f==LOW)
  {
  Blynk.virtualWrite(V1,"SOIL IS WET");
  delay(1500);
  }
  if(f==HIGH)
  {
  Blynk.virtualWrite(V1,"SOIL IS DRY");
  delay(1500);
  }
  if(g==LOW)
  {
   Blynk.virtualWrite(V2,"WATER LEAKAGE DETECTED"); 
   delay(1500); 
  }
  if(g==HIGH)
  {
   Blynk.virtualWrite(V2,"NO LEAKAGE DETECTED"); 
   delay(1500); 
  }
  
}
void loop()
{
  Blynk.run();  
  timer.run();
}
BLYNK_WRITE(V0)
{ 
int a=param.asInt();
if(a==1)
{
  digitalWrite(Relay,HIGH);  
  Serial.println("PUMP TURNED ON");
}
else
{
  digitalWrite(Relay,LOW);   
  Serial.println("PUMP TURNED OFF");    
}
}