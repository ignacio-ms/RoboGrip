#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

#define FLEX_PIN A0

MPU6050 mpu;

int ax, ay, az;
float acc[2];
float flex_deg;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  pinMode(FLEX_PIN, INPUT);
  
  mpu.initialize();
}

void loop() 
{
  // Leer las aceleraciones y giroscopio
  mpu.getAcceleration(&ax, &ay, &az);

  //Calculos angulos X e Y
  acc[0] = atan(ax / sqrt(pow(ay, 2) + pow(az, 2))) * RAD_TO_DEG;
  acc[1] = atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * RAD_TO_DEG;

  //Calcula angulos del sensor de flexion
  flex_deg = analogRead(FLEX_PIN);
  flex_deg = map(flex_deg, 264, 512, 0, 180);

  send_data();
  delay(10);
}

void send_data(){
  Serial.print(acc[0]);
  Serial.print(",");
  Serial.print(acc[1]);
  Serial.print(",");
  Serial.println(flex_deg);
}
