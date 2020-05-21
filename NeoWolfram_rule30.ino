/* Wolfram Cellular Automata 1D in Neopixel LED strip
 *  
 More information on the theory behind the operation of this type of simulation model
 https://www.wolframscience.com/nks/p53--more-cellular-automata/
 
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.

 by gbarbarov@singulardevices.com   
 https://github.com/gbarbarov/led-race 
*/

#include <Adafruit_NeoPixel.h>
#define PIN            2
#define NUMPIXELS      100
#define R_LEVEL        10
#define G_LEVEL        0
#define B_LEVEL        0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

boolean world[NUMPIXELS];
boolean shadow[NUMPIXELS];

//boolean  rule[] = {0,1,1,1,1,0,0,0}; // Rule 30  caos 
//boolean  rule[] = {1,0,0,0,0,0,0,0}; // Rule 1  flash and central point 
//boolean  rule[] = {0,1,0,0,0,0,0,0}; // Rule 2  OPEN LED RACE RIGHT!!!!
//boolean  rule[] = {0,0,1,0,0,0,0,0}; // Rule 4  central point on
//boolean  rule[] = {0,0,0,1,0,0,0,0}; // Rule 8  dead
//boolean  rule[] = {0,0,0,0,1,0,0,0}; // Rule 16  OPEN LED RACE LEFT !!!!
boolean  rule[] = {0,1,0,0,1,0,0,0}; // Rule 18   sierpinsky style !!!!!
//boolean  rule[] = {0,1,0,1,1,0,1,1}; // Rule 18   sierpinsky style !!!!!
//boolean  rule[] = {1,0,1,0,0,0,0,0}; // Rule 5   flash
//boolean  rule[] = {1,0,0,1,0,0,1,0}; // Rule 73  caos
//boolean  rule[] = {1,0,0,0,0,0,0,1};   // Rule 129  sierpinsky !!!!!
//boolean  rule[] = {1,0,0,1,1,0,0,1};   // rule 153 


int dt = 200; // delay 

boolean run_rule (boolean cell_L, boolean cell, boolean cell_R) {
return(rule[cell_L<<2 | cell<<1 | cell_R]);  //fast mode

//didactic mode 
 /* if (cell_L == 0 && cell == 0 && cell_R == 0) return rule[0]; 
    else if (cell_L == 0 && cell == 0 && cell_R == 1) return rule[1];
         else if (cell_L == 0 && cell == 1 && cell_R == 0) return rule[2];
              else if (cell_L == 0 && cell == 1 && cell_R == 1) return rule[3];
                   else if (cell_L == 1 && cell == 0 && cell_R == 0) return rule[4];
                        else if (cell_L == 1 && cell == 0 && cell_R == 1) return rule[5];
                             else if (cell_L == 1 && cell == 1 && cell_R == 0) return rule[6];
                                  else if (cell_L == 1 && cell == 1 && cell_R == 1) return rule[7]; */    
}

void time_tick(){
  for (int n=1;n<NUMPIXELS-1;n++)
  {world[n]=run_rule(shadow[n-1],shadow[n],shadow[n+1]);   
  }
    
  world[0]=run_rule(shadow[NUMPIXELS-1],shadow[0],shadow[1]);  
  world[NUMPIXELS-1]=run_rule(shadow[NUMPIXELS-2],shadow[NUMPIXELS-1],shadow[0]);   
  
  delay(dt);
}

void big_bang(){
  for (int n=0;n<NUMPIXELS;n++)
  {world[n]=0;shadow[n]=0;   
  };   
  world[NUMPIXELS/2]=1; //seed 
  world[1]=1; //seed 
  world[8]=1; //seed 
}

void setup() {  
  pixels.begin();       //Initialize NeoPixel library
  Serial.begin(115200); //Initialize serial port for view patron
  big_bang();
}

void loop() {
     
  for(int i=0;i<NUMPIXELS;i++){   
    pixels.setPixelColor(i, pixels.Color(R_LEVEL*world[i],G_LEVEL*world[i],B_LEVEL*world[i]));
    shadow[i]=world[i];
    if (world[i]) Serial.write('*'); else Serial.write(' '); //ascii mode view  
    //Serial.print(world[i]);                                // binary mode view
    }
    Serial.println(); //end patron   
         
    pixels.show(); // Update LEDs to the hardware.  

    time_tick();
  }
