#include <Wire.h>

#define ADDR 0x01
#define DELAY_T 100

char input[32];
char input2[4];
int flag=0;
int index=0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  pinMode(13,OUTPUT);
  Serial.begin(153600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int inputchar=(char)Serial.read();
  if(inputchar!=-1){
    if (inputchar==100){
      flag=1;
      Wire.beginTransmission(ADDR);
      Wire.write(1);
      Wire.endTransmission(); //full
    }else if (inputchar==101){
      flag=2;
      Wire.beginTransmission(ADDR);
      Wire.write(2);
      Wire.endTransmission(); //delta
    }else if (inputchar==99){
      flag=0;
      Wire.beginTransmission(ADDR);
      for (int i=0; i<4; i++){
        input2[i]=99;
      }
      Wire.write(input2,4);
      Wire.endTransmission(); //stop
    }else if(flag==1){
      input[index]=inputchar-48;
      index++;
    }else if (flag==2){
      input2[index]=inputchar-48;
      index++;
    }
  }
  if (index>=32&&flag==1){
    index=0;
    Wire.beginTransmission(ADDR);
    Wire.write(input,32);
    Wire.endTransmission();
    //delayMicroseconds(10);
  }
  if (flag==2&&index>=4){
    index=0;
    Wire.beginTransmission(ADDR);
    Wire.write(input2,4);
    Wire.endTransmission();
  }
}