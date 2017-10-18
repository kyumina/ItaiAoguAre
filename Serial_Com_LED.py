#coding:utf-8

from PIL import Image
import serial
import time

def light2alpha(light):
    alpha="a"
    if (light==0):
        alpha="a"
    elif (light==1):
        alpha="b"
    elif (light==2):
        alpha="c"
    elif (light==3):
        alpha="d"
    elif (light==4):
        alpha="e"
    elif (light==5):
        alpha="f"
    elif (light==6):
        alpha="g"
    elif (light==7):
        alpha="h"
    elif (light==8):
        alpha="i"
    elif (light==9):
        alpha="j"
    elif (light==10):
        alpha="A"
    return alpha


def main():
    img = Image.open('hogemi32x32.png')
    img.resize((32,32),Image.LANCZOS)
    #img = img.transpose(Image.FLIP_LEFT_RIGHT)
    img = img.transpose(Image.FLIP_TOP_BOTTOM)
    rlist=[]
    glist=[]
    blist=[]

    for i in range(32):
        for j in range(32):
            imgcolor = img.getpixel((i,j))
            print(imgcolor[0])
            rlist.append(int(float(imgcolor[0])/255*10))
            glist.append(int(float(imgcolor[1])/255*10))
            blist.append(int(float(imgcolor[2])/255*10))

    #rlist=[[10 for i in range(32)] for j in range(32)]
    #glist=[[10 for i in range(32)] for j in range(32)]
    #blist=[[10 for i in range(32)] for j in range(32)]

    with serial.Serial('COM4',9600,timeout=1) as ser:
        time.sleep(2)
        for r in rlist:
            ser.write(bytes(light2alpha(r),'utf-8'))
        for g in glist:
            ser.write(bytes(light2alpha(g),'utf-8'))
        for b in blist:
            ser.write(bytes(light2alpha(b),'utf-8'))
        ser.close()

if __name__ == "__main__":
    main()