/*analogWrite(EnA,motorcontrol[1]);
analogWrite(EnB,motorcontrol[0]);*/


/*if(motorcontrol[2] == 1){
 digitalWrite(In1,HIGH);
 digitalWrite(In2,LOW);
 digitalWrite(In3,HIGH);
 digitalWrite(In4,LOW);
  
}else if (motorcontrol[2] == 0){
 digitalWrite(In1,LOW);
 digitalWrite(In2,HIGH);
 digitalWrite(In3,LOW);
 digitalWrite(In4,HIGH);

}
*/

#include <SPI.h>
#include <RH_NRF24.h>
#include <RHReliableDatagram.h>
#define SERVER 2
#define CLIENT 1   

 
int INB = 4;
int IN3 = 5;//connected to analog pins
int IN4 = 9;
int INA = 12;
int IN1 = 7;//connected to analog pins
int IN2 = 2;
 



RH_NRF24 radios;
uint8_t info[RH_NRF24_MAX_MESSAGE_LEN];
RHReliableDatagram radio(radios, SERVER);
 

void setup()
{
  radio.init();
    
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT); } 
 
void loop(){
  if (radio.available()){
    uint8_t frominfo;
    uint8_t lengths = sizeof(info);
    
    if (radio.recvfromAck(info, &lengths, &frominfo)){
 
      if (info[2] == 1)
      {

    //  backwards
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); }
    
    else if (info[2] == 0){
    // forwards

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);}
 
      
      // drive motors
      analogWrite(INB, info[0]);
      analogWrite(INA, info[1]);
      
      }
  }              
}
