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
 *   Demonstrates Esparto "Latching" pin, which is based on a Debounced pin and therefore also requires
 *   a debouncing "timeout" value. Each cycle of up/down changes the state.
 *   
 *  Also demonstrates:
 *    dynamic reconfiguration of initial pin parameters
 *    callback on dynamic reconfiguration
 *   
 *   1) push and release button, LED will flash
 *   2) wait some time
 *   3) push and release button, LED will stop flashing
 *   
 *   HARDWARE REQUIRED: 
 *   
 *      "Tact" style pushbutton on GPIO which pulls it to GND
 */
#define PUSHBUTTON  0
#define DBV         15  // debounce value in mSec
//
//  Gets called when pin configuration changes
//
void onPinConfigChange(uint8_t pin,int v1,int v2){
  if(pin==PUSHBUTTON){
    Serial.printf("Pin %d debounce value has changed v1=%d v2=%d\n",pin,v1,v2);
  } else Serial.printf("Pin %d??? how did THAT happen?\n",pin);
}

void buttonPress(int hilo,int v2){
  Serial.printf("T=%d Latching: state=%d v2=%d\n",millis(),hilo,v2);
  if(hilo) Esparto.stopLED();  // this example is active HIGH
  else Esparto.flashLED(250);
}

void setupHardware(){
    Serial.begin(74880);
    Serial.printf("Esparto %s\n",__FILE__);  
    Serial.printf("Esparto Latching Example, pin=%d dbv=%dms\n",PUSHBUTTON,DBV); 
    Esparto.Output(BUILTIN_LED);                         // start with LED OFF
    Esparto.Latching(PUSHBUTTON,INPUT,DBV,buttonPress);           // 15ms of debouncing
    Esparto.onceRandom(45000,60000,[](){
      Serial.printf("T=%d set debounce value to %d\n",millis(),DBV / 5);
      Esparto.reconfigurePin(PUSHBUTTON,DBV / 5);
   });
}
