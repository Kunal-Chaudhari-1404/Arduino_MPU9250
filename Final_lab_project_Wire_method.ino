#include<Wire.h>

#define    MPU9250_ADDRESS           0x68


void setup() {
  Wire.begin();
  Serial.begin(9600);

  short Val;

  writeRegisterMPU9250(0x77, 50);
  Val = readRegisterMPU9250(0x77);
  Serial.print("Value: ");
  Serial.println(Val);
  Serial.println();
  
  //Reset the device
  writeRegisterMPU9250(0x6B, 0x80);
  delay(100); //delay time in seconds

  writeRegisterMPU9250(0x1C, 0x00);  //configuring to +/- 2g
  delay(100);
}

void loop() {

  signed short X, Y, Z;
 
  //X-Axis
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 2);

  while(Wire.available() < 2);

  X = Wire.read() << 8; 
  X = X + Wire.read();
  
  //Y-Axis
  Wire.beginTransmission(0x68);
  Wire.write(0x3D);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 2);

  while(Wire.available() < 2);

  Y = Wire.read() << 8; 
  Y = Y + Wire.read();
  
  //Z-Axis
  Wire.beginTransmission(0x68);
  Wire.write(0x3F);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 2);

  while(Wire.available() < 2);

  Z = Wire.read() << 8; 
  Z = Z + Wire.read();
  
  Serial.print("X-axis: ");
  Serial.println(X);
  Serial.print("Y-axis: ");
  Serial.println(Y);
  Serial.print("Z-axis: ");
  Serial.println(Z);
  Serial.println();
  short a = 0.0 , b = 0.0, c = 1.0;

  float result = ((float)(X) * a) + ((float)(Y) * b ) + ((float)(Z) * c) / (sqrt(sq((float)(X)) + sq((float)(Y)) + sq((float)(Z))) * sqrt(sq(a) + sq(b) + sq(c)));
  float angle = acos(result);  // angle in radian
  angle = angle * (180 / 3.14);  //angle in degree

  Serial.print("The angle in degrees is: ");
  Serial.println(angle);
  Serial.println();

  delay(1100); //delay time in seconds
  
}

void writeRegisterMPU9250(char address, char data) {
  Wire.beginTransmission(0x68);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

int readRegisterMPU9250(char address) {
  char Val;
  
  Wire.beginTransmission(0x68);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 1);
  
  Val = Wire.read();
 
  return Val;
}
