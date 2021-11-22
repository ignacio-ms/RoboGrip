#include <Servo.h>

#define servo_base_pin 9
#define servo_arm_1_pin 6
//#define servo_arm_2_pin 5
#define servo_grip_pin 3

Servo servo_base;
Servo servo_arm_1;
//Servo servo_arm_2;
Servo servo_grip;

float threshold = 20;
float threshold_flex = 120;

float prev_base_ang = 0;
float prev_arm_ang_0 = 0;
//float prev_arm_ang_1 = 90;

int acc[2];
int flex_deg;

String str;


void setup() {
  Serial.begin(9600);
  
  servo_base.attach(servo_base_pin);
  servo_arm_1.attach(servo_arm_1_pin);
//  servo_arm_2.attach(servo_arm_2_pin);
  servo_grip.attach(servo_grip_pin);
  
  servo_base.write(0);
  servo_arm_1.write(0);
//  servo_arm_2.write(90);
  servo_grip.write(50);
}

void loop() {
  if(Serial.available() > 0){
    str = Serial.readStringUntil('\n');
  }
  
  parse_data();
  str = "";

  move_arm();
  delay(10);
}

void parse_data()
{  
  int ind1, ind2, ind3;
  float acc_0_aux, acc_1_aux, flex_deg_aux;

  ind1 = str.indexOf(',');
  acc[0] = str.substring(0, ind1).toFloat();

  ind2 = str.indexOf(',', ind1+1);
  acc[1] = str.substring(ind1+1, ind2+1).toFloat();

  ind3 = str.indexOf(',', ind2+1);
  flex_deg = str.substring(ind2+1).toFloat(); 
}

void move_arm(){
  /* ----- Base -----*/ 
  if(acc[1] > threshold && prev_base_ang > 0){
    servo_base.write(prev_base_ang - 1);
    prev_base_ang = prev_base_ang - 1;
  } 
  else if(acc[1] < -threshold && prev_base_ang < 180){
    servo_base.write(prev_base_ang + 1);
    prev_base_ang = prev_base_ang + 1;
  }

  /* ----- ARM -----*/
  //dcha
  if(acc[0] > threshold && prev_arm_ang_0 < 50){
    servo_arm_1.write(prev_arm_ang_0 + 1);
    prev_arm_ang_0 = prev_arm_ang_0 + 1;
  } 
  else if(acc[0] < -threshold && prev_arm_ang_0 > 0){
    servo_arm_1.write(prev_arm_ang_0 - 1);
    prev_arm_ang_0 = prev_arm_ang_0 - 1;
  }

  /*
   * Este servo no tiene fuerza para mover su parte del brazo
   */
  //izda
//  if(acc[0] > threshold && prev_arm_ang_1 > 0){
//    servo_arm_2.write(prev_arm_ang_1 - 1);
//    prev_arm_ang_1 = prev_arm_ang_1 - 1;
//  } 
//  else if(acc[0] < -threshold && prev_arm_ang_1 < 130){
//    servo_arm_2.write(prev_arm_ang_1 + 1);
//    prev_arm_ang_1 = prev_arm_ang_1 + 1;
//  }

  /* ----- GRIP -----*/
  if(flex_deg > threshold_flex)
    servo_grip.write(0);
  else if(flex_deg < threshold_flex)
    servo_grip.write(50);
  
}
