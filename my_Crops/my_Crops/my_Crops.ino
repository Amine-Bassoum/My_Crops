#include <SPI.h>
#include <TFT.h>
#include <SoftwareSerial.h>
#define SensorPin 0  
//screen pins
#define cs   10 
#define dc   9
#define rst  8  
TFT TFTscreen = TFT(cs, dc, rst);

SoftwareSerial BTserial(10, 11); 

unsigned long int avgValue;  
float b;
char sensorPrintout[4];
int buf[10],temp;
int sensorPin = A6;
int moistureSensor = A7;
int lightSensor = A8;
int tempSensor = A9;
int sensorValue = 0;
int moisture_val;
int light_val;
int temp_val;

void setup()
{
  pinMode(13,OUTPUT);  
  Serial.begin(9600);  
  Serial.println("Ready");  
  BTserial.begin(9600);
  TFTscreen.begin();
  TFTscreen.background(255,255,255);
  
}
void loop()
{
  for(int i=0;i<10;i++)    
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                  
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; 
  phValue=3.5*phValue;                     
  Serial.print("    pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");
  digitalWrite(13, HIGH);       
  delay(800);
  digitalWrite(13, LOW); 
  int sensorValue = analogRead(A0);
  analogWrite(13, sensorValue * (51.0 / 1023.0) * 50);
  if(sensorValue > 0){
     Serial.println(sensorValue);
     Serial.print(" ");
  moisture_val = analogRead(moistureSensor); // read the value from the moisture-sensing probes
  Serial.print("moisture sensor reads ");
  Serial.println( moisture_val );
  delay(500);
  light_val = analogRead(lightSensor); // read the value from the photosensor
  Serial.print("light sensor reads ");
  Serial.println( light_val );
  delay(500);
  temp_val = analogRead(tempSensor);
  Serial.print("temp sensor reads ");
  Serial.println( temp_val );
  delay(1000);
  sensorValue = analogRead(sensorPin);
  BTserial.print(light_val);
  BTserial.print(",");
  BTserial.print(temp_val);
  BTserial.print(",");
  BTserial.print(moisture_val);
  BTserial.print(",");
  BTserial.print(sensorValue);
  BTserial.print(";");
  delay(20);}
}
