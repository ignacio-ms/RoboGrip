import processing.serial.*;

Serial port;
String port_name;
String str;

float roll, pitch, flex_deg;
float threshold_flex = 120;
PImage logo;

void setup(){
  size(800, 800, P3D);
  
  port_name = Serial.list()[32]; //Es el indice del puerto que corresponde en mi PC
  port = new Serial(this, port_name, 9600);
  
  logo = loadImage("logo.png");
}

void draw(){
  if(port.available() > 0){
    str = port.readStringUntil('\n');
  }
  if(str != null){
    String[] splitted = split(str, ',');
    
    if(splitted.length == 3 && splitted[0] != null && splitted[1] != null && splitted[2] != null){
  
      try {
        pitch = Float.parseFloat(splitted[0]);
        roll = Float.parseFloat(splitted[1]);
        flex_deg = Float.parseFloat(splitted[2]); 
        
        translate(width/2, height/2, 0);
        
        background(105,105,105);
        image(logo, 200, -400, 200, 220);
        
        draw_box("Hand\n", pitch, roll, flex_deg);
      }catch (NumberFormatException e){}
    }
  }
}

void draw_box(String name, float pitch, float roll, float flex_deg) {
    pushMatrix();

    rotateX(radians(pitch));
    rotateZ(radians(roll));
  
    textSize(16);
    
    boolean flexing;
    if (flex_deg > threshold_flex){
      fill(255, 0, 0);
      flexing = true;
    }
    else{
      fill(0, 0, 255);
      flexing = false;
    }
      
    box (160, 40, 300); 
    fill(255, 255, 255);
    text(name, -60, 5, 151);
    popMatrix();
    text( name 
          + "\npitch: " + int(pitch)
          + "\nroll: " + int(roll)
          + "\ngrip flexing: " + (flexing ? "Yes" : "No")
          , 0 -20, 200);
}
