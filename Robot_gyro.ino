#include<Wire.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "EYE.h"
#include "config.h"

Adafruit_SSD1306 display(ImageWidth1, ImageHeight1, &Wire, OLED_RESET);

void setup(){
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);    
  noTone(BUZZER);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { 
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  }
   display.display();
   delay(2);
    
   display.clearDisplay();
   display.setTextColor(WHITE);
   display.setTextSize(2);
   display.setCursor(0,5);
   display.print("SHD.Co");
   display.display();
   delay(2000);
   startTime = millis();
  
}
void loop(){
  currentTime = millis();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
   
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
   
  Serial.print("AngleX= ");
  Serial.println(x);
   
  Serial.print("AngleY= ");
  Serial.println(y);
   
  Serial.print("AngleZ= ");
  Serial.println(z);
  
  Serial.print(" ");
  //Serial.println(te);
  
  Serial.println("--------------------");
  
  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Normal, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(500);
 
  if( currentTime - startTime >= periodTime){
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Blink1, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(50);
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Blink2, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(50);
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Blink3, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(50);
    startTime = currentTime ;
  }   
  if(x <=100){
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_SaadL, ImageWidth1, ImageHeight1, 1);
    display.display();
    tone(BUZZER, freq);
    delay(200);
    noTone(BUZZER);
    delay(1000);
  }
  if(x >=250 && x<=300){
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_SaadR, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(1000);
  }
  if(y <=60){
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Blink2, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(1000);
  }
   
/*
display.clearDisplay();
display.setTextSize(2);
display.setCursor(0,0);
display.print("X: ");
display.println(x);

display.setTextSize(2);
display.setCursor(0,20);
display.print("Y: ");
display.println(y);
 
display.setTextSize(2);
display.setCursor(0,40);
display.print("Z: ");
display.println(z);
display.display();
 
delay(5);
*/
}



/*

void loop() {
  for( int l=0; l<= 2 ; l++) {
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Normal, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(2000);
  
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Blink1, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(50);
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Blink2, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(50);
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Blink3, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(50);
 }
    
  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Happy, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(500);
  
  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Angry, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(500);
  
  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_LookL, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(500);

  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_LookR, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(500);

  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_SaadL, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(500);

  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_SaadR, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(500);

  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Poker, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(500);

  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Off1, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(50);
  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Off2, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(50);
  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Off3, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(1000);

  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Glitch1, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(50);
  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Glitch2, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(50);
  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Glitch3, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(500);

  display.clearDisplay();
  display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Dead, ImageWidth1, ImageHeight1, 1);
  display.display();
  delay(500);

  for (int l=0 ; l<=4 ; l++){
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_SaadL, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(50);
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_CryL1, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(50);
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_CryL2, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(50);
 }
    display.clearDisplay();
    display.drawBitmap(0, (32 - (ImageHeight1 / 2)),  ImageArray_Sheet, ImageWidth1, ImageHeight1, 1);
    display.display();
    delay(1000);

}
*/
