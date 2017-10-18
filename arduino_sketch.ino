#include <Wire.h>

#define ADDR 0x01
#define DELAY_T 100

char input[32];
int flag=0;
int index=0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int inputchar=(char)Serial.read();
  if(inputchar!=-1){
    switch(inputchar){
      case 'a':
        input[index]=(char)0;
        index++;
        break;
      case 'b':
        input[index]=(char)1;
        index++;
        break;
      case 'c':
        input[index]=(char)2;
        index++;
        break;
      case 'd':
        input[index]=(char)3;
        index++;
        break;
      case 'e':
        input[index]=(char)4;
        index++;
        break;
      case 'f':
        input[index]=(char)5;
        index++;
        break;
      case 'g':
        input[index]=(char)6;
        index++;
        break;
      case 'h':
        input[index]=(char)7;
        index++;
        break;
      case 'i':
        input[index]=(char)8;
        index++;
        break;
      case 'j':
        input[index]=(char)9;
        index++;
        break;
      case 'A':
        input[index]=(char)10;
        index++;
        break;
      default:
        input[index]=(char)0;
        index++;
        break;
    }
    if (index>=32){
      index=0;
      Wire.beginTransmission(ADDR);
      Wire.write(input,32);
      Wire.endTransmission();

      delay(10);
    }
  }
}