#include <SoftwareSerial.h>  

JoyState_t joystick;

int bluetoothTx = 7;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 11;  // RX-I pin of bluetooth mate, Arduino D3
int zero = 0x0000;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

int xAxisR = A3;
int yAxisR = A2;
int xAxisL = A1;
int yAxisL = A0;
int xZeroR, yZeroR;
int xZeroL, yZeroL;
int LT, RT;
int DLU, DRD;
int start;
int AB, XY;
int shoulder;
int xValueL, yValueL, xValueR, yValueR;
int deadzone = 5;  // smaller values will be set to 0
unsigned int buttons;
unsigned int blueButtons;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  
	// calculate neutral position
  xZeroR = analogRead(xAxisR);
  yZeroR = analogRead(yAxisR);
  xZeroL = analogRead(xAxisL);
  yZeroL = analogRead(yAxisL);
  
  joystick.xAxis = xZeroR;
  joystick.yAxis = yZeroR;
  joystick.zAxis = 0;
  joystick.xRotAxis = xZeroL;
  joystick.yRotAxis = yZeroL;
  joystick.zRotAxis = 0;
  buttons = 0x0000;
  blueButtons = 0x0000;
  joystick.hatSw1 = 8; //start centered
  joystick.hatSw2 = 8; //start centered
  
  Serial.begin(115200);  // Begin the serial monitor at 9600bps

  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  
  
  
  //bluetooth.print("$");  // Print three times individually
  //bluetooth.print("$");
  //bluetooth.print("$");  // Enter command mode
  //delay(100);  // Short delay, wait for the Mate to send back CMD
  //bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  //bluetooth.begin(9600);
  pinMode(bluetoothTx, INPUT_PULLUP);  
  pinMode(bluetoothRx, OUTPUT);
    
}

void loop() {
  buttons = 0x0000;
  blueButtons = 0x0000;
  
  xValueL = analogRead(xAxisL) - xZeroL;
  yValueL = analogRead(yAxisL) - yZeroL;
  xValueR = analogRead(xAxisR) - xZeroR;
  yValueR = analogRead(yAxisR) - yZeroR;
  
  if(abs(xValueL) < deadzone) {
		xValueL = 0;
	}
	if(abs(yValueL) < deadzone) {
		yValueL = 0;
	}
        if(abs(xValueR) < deadzone) {
		xValueR = 0;
	}
	if(abs(yValueR) < deadzone) {
		yValueR = 0;
	}

	joystick.xRotAxis = map(xValueR, -530, 530, 0, 255);  // here the axis is inverted
	joystick.yRotAxis = map(yValueR, 530, -530, 0, 255);
        joystick.xAxis = map(xValueL, -530, 530, 0, 255);  // here the axis is inverted
	joystick.yAxis = map(yValueL, 530, -530, 0, 255);

  LT = analogRead(A4);
  RT = analogRead(A5);
  
  if(LT<15)
    LT = 0;
    
  if(RT<370)
    RT = 370;
    
  if(LT > 600)
    blueButtons += 0x0800;
  if(RT > 600)
    blueButtons += 0x0400;
    
  joystick.zAxis = (map(LT,0,1023,0,128)+map(RT,370,1023,0,-127))+127;
  Serial.println(RT);
  //joystick.zAxis = map(LT,15,360,0,255);
  //joystick.rudder = map(RT,370,1023,0,255);
  
  
  DLU = analogRead(A6);
  DRD = analogRead(A7);
  
  if(DLU > 1000) { //neither pressed
    if(DRD > 1000) {
       joystick.hatSw1 = 8; 
    } else if(DRD > 500) {
       joystick.hatSw1 = 4;
       blueButtons += 0x2000;
    } else if(DRD > 340) {
       joystick.hatSw1 = 2;
       blueButtons += 0x8000;
    } else {
       joystick.hatSw1 = 3; 
       blueButtons += 0xA000; //1010
    }
  } else if(DLU > 500) { //just up
    if(DRD > 1000) {
       joystick.hatSw1 = 0;
       blueButtons += 0x1000; 
    } else if(DRD < 500) {
       joystick.hatSw1 = 1;
       blueButtons += 0x9000;
    } else {
      joystick.hatSw1 = 0;
      blueButtons += 0x1000;
    } 
  } else if(DLU>90) { //just left
      if((DRD < 600 && DRD > 400) || DRD < 300) {
        joystick.hatSw1 = 5;
        blueButtons += 0x6000;
      } else {
        joystick.hatSw1 = 6;
        blueButtons += 0x4000;
      }
  } else { //upleft
    joystick.hatSw1 = 7;
    blueButtons += 0x5000;
  }
  
  start = analogRead(A11);
  
  if(start < 300){
    buttons += 0x00C0; 
  } else if (start < 400){
    buttons += 0x0080;
  } else if(start < 1000) {
    buttons += 0x0040;
  }
  
  shoulder= analogRead(A10);
  
  if(shoulder < 300){
    buttons += 0x0030; 
  } else if (shoulder < 400){
    buttons += 0x0020;
  } else if(shoulder < 1000) {
    buttons += 0x0010;
  }

  
  AB = analogRead(A8);

  if(AB < 300){
    buttons += 0x0003; 
  } else if (AB < 400){
    buttons += 0x0002;
  } else if(AB < 1000) {
    buttons += 0x0001;
  }  
  
  XY = analogRead(A9);
  
  if(XY < 300){
    buttons += 0x000C; 
  } else if (XY < 400){
    buttons += 0x0004;
  } else if(XY < 1000) {
    buttons += 0x0008;
  }
  
  if(!digitalRead(2))
    buttons += 0x0200;
    
  if(!digitalRead(3))
    buttons += 0x0100;
    
  joystick.buttons = buttons;
  
  blueButtons += buttons;
  byte blue1 = blueButtons;
  byte blue2 = blueButtons>>8;
  
     bluetooth.write(0xFD); //raw data
     delay(2);
     bluetooth.write(0x06); //joystick
     delay(2);
     bluetooth.write(map(joystick.xAxis,0,1024,-128,127)); //xaxis
     delay(2);
     bluetooth.write(map(joystick.yAxis,0,1024,-128,127)); //yaxis
     delay(2);
     bluetooth.write(map(joystick.xRotAxis,0,1024,-128,127)); //z
     delay(2);
     bluetooth.write(map(joystick.yRotAxis,0,1024,-128,127)); //xrot
     delay(2);
     bluetooth.write(blue1); //1-16
     delay(2);
     bluetooth.write(blue2); //1-16
     delay(2);
     
  
  Joystick.setState(&joystick);
  
  //delay(1000);
}
