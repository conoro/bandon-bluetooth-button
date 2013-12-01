/*
  BPLib.cpp - Library for communication with RN-42 HID Bluetooth module
  Created by Basel Al-Rudainy, 6 april 2013.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/
#include "Arduino.h"
#include "BPLib.h"

BPLib::BPLib(){
pinMode(7,INPUT);
digitalWrite(7,LOW);
}

byte BPLib::begin(char BP_Mode[], char BP_Type[])
{
Serial.begin(115200);
Serial.print(BP_MODE_COMMAND);
  if (get(BP_STAT_CMD, (byte)5)!=1) {
    return (byte)0;
  }//if
  
  Serial.print(BP_Mode);
  if (get(BP_STAT_ACK, (byte)5)!=1) {
    return (byte)0;
  }//if
  if(strcmp(BP_Type,BP_SPP_SPP)>0){
  Serial.print(BP_Type);
  if (get(BP_STAT_ACK, (byte)5)!=1) {
    return (byte)0;
  }//if
  }
  Serial.print(BP_REBOOT);
  if (get(BP_STAT_REBOOT, (byte)9)!=1) {
    return (byte)0;
  }//if
  delay(1000); //Delay (Bluetooth boot-up)

return (byte)1;
}

byte BPLib::sendCmd(char BP_CMD[])
{
  Serial.print(BP_MODE_COMMAND);
  if (get(BP_STAT_CMD, (byte)5)!=1) {
    return (byte)0;
  }//if
  Serial.print(BP_CMD);
  if (get(BP_STAT_ACK, (byte)5)!=1) {
    return (byte)0;
  }//if
  Serial.print(BP_MODE_EXITCOMMAND);
  if (get(BP_STAT_END, (byte)5)!=1) {
    return (byte)0;
  }//if
  return (byte)1;
}

byte BPLib::readRaw(){
return Serial.read();
}
int BPLib::available(){
return Serial.available();
}

byte BPLib::get(char BP_STAT[],byte strlen)
{
char buffer[strlen + 1];
  while (Serial.available() <= (strlen-1)) {};
    int count = 0;
    while (Serial.available() > 0) {
      buffer[count]=(char)Serial.read();
      count++;
    }//while
  buffer[strlen]=0;
    //Serial.print(buffer);//DEBUG
    if (strcmp(buffer,BP_STAT)==0) {
      return (byte)1;
    }//if
    else {
      return (byte)0;
    }//else
}//get


void BPLib::keyboardPress(byte BP_KEY,byte BP_MOD){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x9); //Length byte
Serial.write((byte)0x1); //Descriptor byte
Serial.write(BP_MOD); //Modifier byte
Serial.write((byte)0x00); //-
Serial.write(BP_KEY); //Send KEY
for(byte i = 0;i<5;i++){ //Send five zero bytes
Serial.write((byte)0x00);
}

}

void BPLib::keyboardReleaseAll(){
keyboardPress((byte)0x00,BP_MOD_NOMOD);
}

void BPLib::mouseClick(byte BP_BUTTON){
mousePress(BP_BUTTON);
mouseReleaseAll();
}
void BPLib::mouseMove(signed int BP_X,signed int BP_Y){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x5); //Length byte
Serial.write((byte)0x2); //Descriptor byte
Serial.write((byte)0x00); //Button byte
Serial.write(BP_X);	//(-127 to 127)
Serial.write(BP_Y);	//(-127 to 127)
Serial.write((byte)0x00);

}
void BPLib::mousePress(byte BP_BUTTON){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x5); //Length byte
Serial.write((byte)0x2); //Descriptor byte
Serial.write(BP_BUTTON); //Button byte
for(byte i = 0;i<3;i++){ //Send three zero bytes
Serial.write((byte)0x00);
}
}

void BPLib::mouseReleaseAll(){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x5); //Length byte
Serial.write((byte)0x2); //Descriptor byte
for(byte i = 0;i<4;i++){ //Send four zero bytes
Serial.write((byte)0x00);
}
}

void BPLib::mouseWheel(signed int BP_WHEEL){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x5); //Length byte
Serial.write((byte)0x2); //Descriptor byte
for(byte i = 0;i<3;i++){ //Send three zero bytes
Serial.write((byte)0x00);
}
Serial.write(BP_WHEEL); //Wheel byte (-127 to 127)
}

void BPLib::volumeUp(){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x3); //Length byte
Serial.write((byte)0x3); //Descriptor byte
Serial.write((byte)0x10); //LowByte
Serial.write((byte)0x00); //HighByte
}

void BPLib::volumeDown(){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x3); //Length byte
Serial.write((byte)0x3); //Descriptor byte
Serial.write((byte)0x20); //LowByte
Serial.write((byte)0x00); //HighByte
}

void BPLib::muteAudio(){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x3); //Length byte
Serial.write((byte)0x3); //Descriptor byte
Serial.write((byte)0x40); //LowByte
Serial.write((byte)0x00); //HighByte
}

void BPLib::playPause(){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x3); //Length byte
Serial.write((byte)0x3); //Descriptor byte
Serial.write((byte)0x80); //Play/Pause Press Down LowByte
Serial.write((byte)0x00); //Play/Pause Press Down HighByte
}

void BPLib::nextTrack(){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x3); //Length byte
Serial.write((byte)0x3); //Descriptor byte
Serial.write((byte)0x00); //LowByte
Serial.write((byte)0x01); //HighByte
}

void BPLib::prevTrack(){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x3); //Length byte
Serial.write((byte)0x3); //Descriptor byte
Serial.write((byte)0x00); //LowByte
Serial.write((byte)0x02); //HighByte
}

void BPLib::stopAudio(){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x3); //Length byte
Serial.write((byte)0x3); //Descriptor byte
Serial.write((byte)0x00); //LowByte
Serial.write((byte)0x04); //HighByte
}

void BPLib::fastForwardAudio(){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x3); //Length byte
Serial.write((byte)0x3); //Descriptor byte
Serial.write((byte)0x00); //LowByte
Serial.write((byte)0x10); //HighByte
}

void BPLib::rewindAudio(){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x3); //Length byte
Serial.write((byte)0x3); //Descriptor byte
Serial.write((byte)0x00); //LowByte
Serial.write((byte)0x20); //HighByte
}

void BPLib::keyRelease(){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x3); //Length byte
Serial.write((byte)0x3); //Descriptor byte
Serial.write((byte)0x00); //Key Release LowByte
Serial.write((byte)0x00); //Key Release HighByte
}


byte BPLib::changeName(char BP_NAME[]){
 Serial.print(BP_MODE_COMMAND);
  if (get(BP_STAT_CMD, (byte)5)!=1) {
    return (byte)0;
  }//if
  Serial.print(BP_CHANGE_NAME);
  Serial.print(BP_NAME);
  Serial.print(F("\r\n"));
  if (get(BP_STAT_ACK, (byte)5)!=1) {
    return (byte)0;
  }//if
  Serial.print(BP_MODE_EXITCOMMAND);
  if (get(BP_STAT_END, (byte)5)!=1) {
    return (byte)0;
  }//if
  return (byte)1;

}


void BPLib::sendByte(byte rawData){
Serial.print(rawData);
}
void BPLib::sendChar(char rawData){
Serial.print(rawData);
}
void BPLib::sendInt(int rawData){
Serial.print(rawData);
}
void BPLib::sendFloat(float rawData){
Serial.print(rawData);
}
void BPLib::sendLong(long rawData){
Serial.print(rawData);
}
void BPLib::sendString(char rawData[]){
Serial.print(rawData);
}

void BPLib::gameJoyPress(byte BP_ST_BTN, byte BP_ND_BTN){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x6); //Length byte
Serial.write((byte)BP_ST_BTN); //First Button byte
Serial.write((byte)BP_ND_BTN); //Second Button byte
for(byte i = 0;i<4;i++){ //Send four zero bytes
Serial.write((byte)0x00);
}
}
void BPLib::gameJoyMove(signed int BP_X1,signed int BP_Y1,signed int BP_X2,signed int BP_Y2){
Serial.write((byte)0xFD); //Start HID Report
Serial.write((byte)0x6); //Length byte
Serial.write((byte)BP_GAMEJOY_ST_NOBTN); //First Button byte
Serial.write((byte)BP_GAMEJOY_ND_NOBTN); //Second Button byte
Serial.write(BP_X1 & 0xFF);	//First X coordinate
Serial.write(BP_Y1 & 0xFF);	//First Y coordinate
Serial.write(BP_X2 & 0xFF);	//Second X coordinate
Serial.write(BP_Y2 & 0xFF);	//Second Y coordinate
}
void BPLib::gameJoyReleaseAll(){
gameJoyPress(BP_GAMEJOY_ST_NOBTN, BP_GAMEJOY_ND_NOBTN);
}

byte BPLib::connected(){
return digitalRead(7);
}
