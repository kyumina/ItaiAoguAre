# ItaiAoguAre

## 技術的構成
PC=(Serial)=>Arduino=(I2C)=>Nucleo

## APIReference
描画モードを2つ用意している
- Full Transfer (全面描画値更新)
- Delta Transfer (index指定描画更新)
最初の一度目など、背景を設定したい場合はFullTransferを選択
個別にLEDの色の変更を行うならDeltaTransgerを利用することをオススメする

### PC2Arduino(Serial)
最初に制御転送をする0x64->Full 0x65->Deltaになる。

#### Full(0x64)
LEDパネルのRGB全面に対する更新を行うため、合計96回の転送を行う必要がある。
値は必ずbytes(chr(value+48),'utf-8')する必要があり、valueは0~10のintかcharの1バイトの指定である。なお48を足しているのは ASCII文字列として認識させる為である。

#### Delta(0x65)
LEDパネルの格点に対して更新を行うため、指定用のcolor,x,y,valueの値を必要とする。
colorはR:48,G:49,B:50のint型である。x,yは0~32である。valueは0~10である。
転送終了時は終了バイト0x63を転送する。

### Arduino2Nucleo(I2C)
最初に制御転送をする、1:Full,2:Deltaとなる。

#### Full(1)
char[32]でvalue(0~10)を送信する。

#### Delta(2)
char[4]でcolor(0~2),x(0~31),y(0~31),value(0~10)を指定する。
転送終了時はcolor,x,y,valueにそれぞれ0x63をいれて転送する。