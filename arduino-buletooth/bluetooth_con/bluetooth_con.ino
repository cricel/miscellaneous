#include "libraries.h"

unsigned long previousMillis = 0;
const long updaterate = 90;
int messageselection = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= updaterate) {
    previousMillis = currentMillis;
    messagehandle();
  }
  dataParsing();
}

void messagehandle(){
  if (messageselection == 0){
    sendIMU();
    messageselection = 1;
  }
  else if (messageselection == 1){
    sendJoyInput();
    messageselection = 0;
  }
}

void dataParsing(){
  if (Serial.available() > 0){
    char tmpChar = Serial.read();
    if ((msgBufferPointer == 0) && (tmpChar == '<')){
      msgBuffer[msgBufferPointer] = tmpChar; 
      msgBufferPointer++;
    }
    else if (msgBufferPointer == 1){
      if (tmpChar == '!'){ 
        msgBuffer[msgBufferPointer] = tmpChar; 
        msgBufferPointer++; 
      }
      else{
        if (tmpChar == '<'){
          msgBufferPointer = 1;
        }else{
          msgBufferPointer = 0;          
        }
      }
    }
    else if (msgBufferPointer == 2){
      if (tmpChar == ' '){
       msgBuffer[msgBufferPointer] = tmpChar; 
        msgBufferPointer++;         
      }else{
        if (tmpChar == '<'){
          msgBufferPointer = 1;
        }else{
          msgBufferPointer = 0;          
        }        
      }    
    }
    else if (msgBufferPointer > 2) {
      if (( msgBuffer[1] == '!') && (msgBuffer[3]-1 == msgBufferPointer)) {
        evaluateCommand();
        msgBufferPointer = 0;
      }
      else{
        msgBuffer[msgBufferPointer] = tmpChar;
        msgBufferPointer++;
      }
    }
    else if (msgBufferPointer > MESSAGE_BUFFER_SIZE){ 
      msgBufferPointer = 0;
    }
  }
}

void evaluateCommand(){
  if (msgBuffer[4] == MSG_SEND_JOYINPUT){
    joy_incoming();
  }
  if (msgBuffer[4] == MSG_SEND_IMU){
    imu_incoming();    
  }
}

//------------------
//receiving Data
//------------------

//receive two float number
void imu_incoming(){ 
  controller_roll[0] = msgBuffer[5];
  controller_roll[1] = msgBuffer[6];
  controller_roll[2] = msgBuffer[7];
  controller_roll[3] = msgBuffer[8];

  controller_pitch[0] = msgBuffer[9];
  controller_pitch[1] = msgBuffer[10];
  controller_pitch[2] = msgBuffer[11];
  controller_pitch[3] = msgBuffer[12];

  controller_yaw[0] = msgBuffer[13];
  controller_yaw[1] = msgBuffer[14];
  controller_yaw[2] = msgBuffer[15];
  controller_yaw[3] = msgBuffer[16];
  controllerIMU.roll = *((float*)(controller_roll));
  controllerIMU.pitch = *((float*)(controller_pitch));
  controllerIMU.yaw = *((float*)(controller_pitch));
}

//receive 4 one byte int
void joy_incoming(){
  joyl_sw = msgBuffer[5];
  joyl_x = msgBuffer[6];
  joyl_y = msgBuffer[7];
}

//------------------
//Sending Data
//------------------

void sendIMU(){
  Serial.write("<! ");
  Serial.write(18);
  Serial.write(MSG_SEND_DRONE_IMU);
  Serial.write((char*)&droneIMU.roll, 4);
  Serial.write((char*)&droneIMU.pitch, 4);
  Serial.write((char*)&droneIMU.yaw, 4);
  Serial.write(">");
}

void sendJoyInput(){
  Serial.write("<! ");
  Serial.write(9);
  Serial.write(MSG_SEND_JOYINPUT);
  Serial.write(joyl_sw);
  Serial.write(joyl_x);
  Serial.write(joyl_y);
  Serial.write(">");
}
