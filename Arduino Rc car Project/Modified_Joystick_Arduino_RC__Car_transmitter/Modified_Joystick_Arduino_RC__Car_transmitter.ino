#include <SPI.H>
#include <RH_NRF24.h>
#include <RHReliableDatagram.h>

#define CLIENT 1
#define SERVER 2

RH_NRF24 radios;

RHReliableDatagram radio(radios,CLIENT);

#define joyhorz  A3 // analog pin connected to x output
#define joyvert  A4 // analog pin connected to y output

int joyVert = 512;
int joyHorz = 512;

uint8_t motor[3];

//definemessage buffer
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];

//int receiver = 13;

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

if(!radio_manager.init())
  Serial.println("init failed");

  motor[2] = 0;//forward

}

void loop() {

Serial.println("motor values ");

joyHorz = analogRead(joyhorz);
joyVert = analogRead(joyvert);

if(joyVert < 453){
  
  motor[2] = 1;//backward;

  //motor speeds(determining)
 //as we're going backward we need to reverse reading
    motor[0] = map(joyVert,453,0,0,255);
    motor[1] = map(joyVert,453,0,0,255);

  
  }  else if(joyvert > 558){
    
    motor[2] = 0;//foward
    
    //determine motor speeds

    motor[0] = map(joyVert,558,1023,0,255);
    motor[1] = map(joyVert,558,1023,0,255);
    
    
    }else

    {
      //stop motors from running
     motor[0] = 0;
     motor[1] = 0;
     motor[2] = 0;
    }

     if(joyHorz < 453){
 
 
    joyHorz = map(joyHorz,453,0,0,255);

    motor[0] -= joyHorz;//decreases left motor
    motor[1] += joyHorz;//increases right motor

    //dont exceed range of 0-255 for motor speeds
    if(motor[1] > 255)
    motor[1] = 255;

    if(motor[0] < 0)
    motor[0] = 0;
    
      
     }else if (joyHorz > 558){
 /* move right. 
 Map the number to a value of 255 maximum*/
 
    joyHorz = map(joyHorz,558,1023,0,255);

    motor[0] += joyHorz;//increase left motor
    motor[1] -= joyHorz;//decrease right motor

    //dont exceed range of 0-255 for motor speeds
    if(motor[1] < 0)
    motor[1] = 0;

    if(motor[0] > 255)
    motor[0] = 255;

}

/*Serial.print("motor A: ");
Serial.print(motor[0]);
Serial.print("motor B: ");
Serial.print(motor[1]);
Serial.print("Direction ");
Serial.print(motor[2]);
analogWrite(EnA,motor[1]);
analogWrite(EnB,motor[0]);
if(joyVert < 453){
  
  motorcontrol[2] = 1;//backward;

  //motor speeds(determining)
 //as we're going backward we need to reverse reading
    motor[0] = map(joyVert,453,0,0,255);
    motor[1] = map(joyVert,453,0,0,255);

  
  }  else if(joyvert > 558){
    
    motor[2] = 0;//foward
    
    //determine motor speeds

    motor[0] = map(joyVert,558,1023,0,255);
    motor[1] = map(joyVert,558,1023,0,255);
    
    
    }*/

if (radio.sendtoWait(motor,sizeof(motorcontrol),SERVER)){

Serial.println("Done");

     delay(150);// wait a bit before next transmission*/

}
   

