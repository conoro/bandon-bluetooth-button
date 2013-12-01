/*
Bandon Bluetooth Button with RN42
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
  // Check X-Axis Pot on Joystick
  int xAxis = analogRead(A0);
  int yAxis = analogRead(A1);
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

