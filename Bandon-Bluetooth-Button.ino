/*
  Bandon Bluetooth Button with RN42 HID. Control media on mobile phones using a joystick/button and Bluetooth.

  Copyright (C) 2013 Conor O'Neill

  Original BPLib Arduino Library is Copyright Basel Al-Rudainy, 6 april 2013. https://github.com/baselsw/BPLib with modifications by Conor O'Neill

  Conor O'Neill's code is Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/


#include <BPLib.h>

const int buttonPin = 2;    // the number of the pushbutton pin

BPLib BPMod;
void setup(){
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  BPMod.begin(BP_MODE_HID,BP_HID_COMBO);
  delay(1000);
}

void loop(){
  // Check X-Axis Pot on Joystick on Analogue Pin A0
  int xAxis = analogRead(A0);

  // Check Y-Axis Pot on Joystick on Analogue Pin A1
  int yAxis = analogRead(A1);

  // Check for button press
  int button = digitalRead(buttonPin);
  
  
  if (xAxis < 400){
    // X to the Left = Prev Track
    BPMod.prevTrack();

    // slight delay to avoid flooding RN42. Probably far too conservative
    delay(250);

    // "lift" the key
    BPMod.keyRelease();
    
    // longer delay to give me chance to let go of joystick
    delay(500);
  }
  else if (xAxis > 700){
    // X to the Right = Next Track
    BPMod.nextTrack();

    // slight delay to avoid flooding RN42. Probably far too conservative
    delay(250);

    // "lift" the key
    BPMod.keyRelease();
    
    // longer delay to give me chance to let go of joystick
    delay(500);
  }  


  // Check Y-Axis Pot on Joystick
  if (yAxis < 400){
    // Y Down = Volume Down
    BPMod.volumeDown();

    // slight delay to avoid flooding RN42. Probably far too conservative
    delay(250);

    // "lift" the key
    BPMod.keyRelease();
    
    // longer delay to give me chance to let go of joystick
    delay(250);
  }
  else if (yAxis > 700){
    // Y Up = Volume Up
    BPMod.volumeUp();

    // slight delay to avoid flooding RN42. Probably far too conservative
    delay(250);

    // "lift" the key
    BPMod.keyRelease();
    
    // longer delay to give me chance to let go of joystick
    delay(250);
  }  
  
  
  // Check Button Press on Joystick
  // Toggle Play/Pause if pressed
  if (button == LOW){
    BPMod.playPause();

    // slight delay to avoid flooding RN42. Probably far too conservative
    delay(250);

    // "lift" the key
    BPMod.keyRelease();
    
    // longer delay to give me chance to let go of joystick button
    delay(500);    
  } 
 // delay(500);    
}

