
/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll & Yaw Gyroscope Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.0003;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;
float xGyro = 0;
float yGyro = 0;
float zGyro = 0;
int X = 0;
int Y = 0;
int Z = 0;
int num;
int incomingByte;
const int button1Pin = 3;
String val;
float rate_gyr_x;
float rate_gyr_y;
float rate_gyr_z;
float gyroXangle;
float gyroYangle;
float gyroZangle;
float CFangleX;
float CFangleY;
float CFangleZ;

float AA = 0.97;
float G_GAIN = 0.070;

Vector rawGyro;
Vector rawAccel;

void setup() 
{
  Serial.begin(9600);
  pinMode(button1Pin, INPUT);
  
  // Initialize MPU6050
  
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
  }
  
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);

  //Serial.println("Finished setup");
}

void loop()
{
  timer = millis();
  
if(Serial.available() > 0){
    //The variable incomingByte contains the incoming infromation
    incomingByte = Serial.read();
    
    //if incomingByte is equal to the character of p 
   //then the arduino will send the analog information of poteniometers
    if(incomingByte == 'p')
    {
      sendData();
    }

    //If the incomingByte is equal to r then pitch,roll and yaw are set to 0.0
    if(incomingByte == 'r')
    {
      pitch = 0.0;
      roll = 0.0;
      yaw = 0.0;
    }

    //When the button is pressed send e to the game else send 0
    if(digitalRead(button1Pin) == HIGH)
    {
      val = 'e';
    }
    else
    {
      val = '0';
    }
    
}

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();
  Vector axis = mpu.readNormalizeAccel();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;
  
  X = axis.XAxis;
  Y = axis.YAxis;
  Z = axis.ZAxis;

  
  
  // Output raw
  /*
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);

  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
  */
}

void sendData()
{
  //The code below send the data from the GyroScope via the specifc port and creates a new line after val
  Serial.print(pitch);
  Serial.print(",");
  Serial.print(roll);
  Serial.print(",");
  Serial.print(yaw);
  Serial.print(",");
  Serial.print(X);
  Serial.print(",");
  Serial.print(Y);
  Serial.print(",");
  Serial.print(Z);
  Serial.print(",");
  Serial.println(val);
}
