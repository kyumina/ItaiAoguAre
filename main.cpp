#include "mbed.h"

#define SDA PB_9
#define SCL PB_8
#define ADDR 0x02

DigitalOut myled(LED1);

DigitalOut R0(D2);
DigitalOut G0(D3);
DigitalOut B0(D4);
DigitalOut R1(D5);
DigitalOut G1(D6);
DigitalOut B1(D7);

DigitalOut CLK(D8);
DigitalOut LAT(D10);
DigitalOut OE(D9,1);

BusOut line_select(A0,A1,A2,A3);

I2CSlave slave(SDA,SCL);
Serial pc(SERIAL_TX,SERIAL_RX);

Ticker ticker;

uint8_t F_BUF_R[32][32];
uint8_t F_BUF_G[32][32];
uint8_t F_BUF_B[32][32];
uint8_t count=0;
static uint8_t line=0;
static uint8_t PWM=0;

char getmode;
char msg[32];
char msg2[4];

void timerIsr()//10KHz
{
    uint8_t x;
    OE=1;
    for(x=0;x<32;x++){
        B0=F_BUF_B[line][x]>PWM;
        B1=F_BUF_B[line+16][x]>PWM;
        R0=F_BUF_R[line][x]>PWM;
        R1=F_BUF_R[line+16][x]>PWM;
        G0=F_BUF_G[line][x]>PWM;
        G1=F_BUF_G[line+16][x]>PWM;
        CLK=1;
        CLK=0;
    }
    OE=1;//o—ÍOFF
    LAT=1;
    LAT=0;
    //printf("%d",line);

    line_select=line;

    OE=0;
    if(++line>15){
        line=0;
        PWM++;
        if(PWM>=10)PWM=0;
    }
}


int main() {
    slave.frequency(100000); //100kHz
    slave.address(ADDR);

    ticker.attach_us(&timerIsr, 100);//100uS,10KHz
    wait(0.2); // 200 ms

    int lines=0;
    int panel=0;
    int flag=0;

    while(1){
        if (slave.receive()){
            if (flag==0){
                getmode=slave.read();
                if (getmode==1){
                    flag=1;
                }else if(getmode==2){
                    flag=2;
                }
            }else if(flag==1){
                slave.read(msg,32);

                if (panel==0){
                    for (int k=0; k<32; k++){
                        F_BUF_R[lines][k]=msg[k];
                    }
                }else if(panel==1){
                    for (int k=0; k<32; k++){
                        F_BUF_G[lines][k]=msg[k];
                    }
                }else if(panel==2){
                    for (int k=0; k<32; k++){
                        F_BUF_B[lines][k]=msg[k];
                    }
                }
                lines++;
                if (lines>=32){lines=0;panel++;}
                if (panel>=3){panel=0;flag=0;}

            }else if(flag==2){
                slave.read(msg2,4);
                if (msg2[0]==0){
                    F_BUF_R[msg2[2]][msg2[1]]=msg2[3];
                }else if(msg2[0]==1){
                    F_BUF_G[msg2[2]][msg2[1]]=msg2[3];
                }else if(msg2[0]==2){
                    F_BUF_B[msg2[2]][msg2[1]]=msg2[3];
                }else if(msg2[0]==99){
                    flag=0;
                }
            }
        }
        /*
        for (int i=0; i<32; i++){
            for (int j=0; j<32; j++){
                F_BUF_R[i][j]=10.0;
                F_BUF_G[i][j]=10.0;
                F_BUF_B[i][j]=10.0;
            }
        }
        */

        wait_us(10);
    }
}