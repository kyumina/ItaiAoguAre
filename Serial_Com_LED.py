#coding:utf-8

from PIL import Image
import serial
import time

def main():
    img = Image.open('20091121232442.png')
    #img.resize((32,32),Image.LANCZOS)
    img.convert("RGB")
    #img = img.transpose(Image.FLIP_LEFT_RIGHT)
    img = img.transpose(Image.FLIP_TOP_BOTTOM)
    rlist=[]
    glist=[]
    blist=[]

    for i in range(32):
        for j in range(32):
            imgcolor = img.getpixel((i,j))
            rlist.append(int(float(imgcolor[0])/255*10))
            glist.append(int(float(imgcolor[1])/255*10))
            blist.append(int(float(imgcolor[2])/255*10))

    #rlist=[i%10 for i in range(32*32)]
    #glist=[i%10 for i in range(32*32)]
    #blist=[i%10 for i in range(32*32)]

    with serial.Serial('COM4',153600,timeout=1) as ser:
        time.sleep(2)
        ser.write(bytes(chr(100),'utf-8')) #full trans
        for r in rlist:
            ser.write(bytes(chr(r+48),'utf-8'))
        for g in glist:
            ser.write(bytes(chr(g+48),'utf-8'))
        for b in blist:
            ser.write(bytes(chr(b+48),'utf-8'))

        time.sleep(1)
        ser.write(bytes(chr(101),'utf-8')) #delta trans
        for x in range(32):
            ser.write(bytes(chr(0+48),'utf-8')) #color
            ser.write(bytes(chr(x+48),'utf-8')) #x
            ser.write(bytes(chr(x+48),'utf-8')) #y
            ser.write(bytes(chr(10+48),'utf-8')) #value(light)
        ser.write(bytes(chr(99),'utf-8'))
        ser.close()

if __name__ == "__main__":
    main()
