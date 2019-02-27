/*
 MIT License

Copyright (c) 2019 Phil Bowles <esparto8266@gmail.com>
                      blog     https://8266iot.blogspot.com     
                support group  https://www.facebook.com/groups/esp8266questions/
                
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <ESPArto.h>
ESPArto  Esparto;
//
/*  
 *   Demonstrates Esparto "Encoder" handling. Rotary Encoders require two pins (often called A and B)
 *   
 *   This simple form of Encoder returns -1 or +1 depending on click direction  
 
 *   HARDWARE REQUIRED: 
 *   
 *   You will need a rotary Encoder for this demo, preferably a very "noisy" one
 *   
 *   change A & B values below to match the chosen pins of your encoder
 *   if you use an external PULLUP (10k recommended) use INPUT
 *   if not using external pullup                    use INPUT_PULLUP
 *   
 *   If your values "go the wrong way" simply swap the A and B pins
 *   
 *   current value is shown every second as well as on change
 *   
 */
#define A  5  // D1 on a Wemos D1 Mini
#define B  4  // D2 ...

int value=42;

void pinChange(int dir,int t){
  Serial.printf("T=%d Encoder click: dir=%d t=%d\n",millis(),dir,t);
  value+=dir;
}

void setupHardware(){
    Serial.begin(74880);
    Serial.printf("Esparto %s\n",__FILE__);      
    Serial.printf("Esparto simple +/- Encoder Example, pinA=%d pinB=%d\n",A,B); 
    Esparto.Encoder(A,B,INPUT,pinChange);
    Esparto.every(1000,[](){
      Serial.printf("T=%d current value is %d\n",millis(),value);
      });
}
