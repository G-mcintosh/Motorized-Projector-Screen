/*
  IR Receiver Demonstration 3
  IR-Rcv-Demo3.ino
  Control LED's using Unused IR Remote keys

  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/

// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>
// Define sensor pin
const int RECV_PIN = 6;
// Define integer to remember toggle state
int togglestate = 1;
// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;
//IR send object
IRsend irsend;

// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 4
#define EnablePin 9
#define stepsPerRevolution 200


// Number of rotations to completely lower screen
int Rotations = 226;





void setup(){
  // Enable the IR Receiver
  irrecv.enableIRIn();
  Serial.begin(9600);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(EnablePin, OUTPUT);

  digitalWrite(EnablePin, HIGH);
  
}


void loop(){
    if (irrecv.decode(&results)){

        switch(results.value){

//Projector Signal relay
          
          case 0x438E0879: //Power Button
          irsend.sendNEC(0xFF15EA, 32);
          //FF15EA
          Serial.println("Proector Power");
          delay(200);
          irrecv.enableIRIn();
          break;

          case 0x14036CA3: //Volume up
          Serial.println("Volume Up");
          delay(200);
          irrecv.enableIRIn();
          break;    

          case 0x20B81A95: //Volume down
          irsend.sendNEC(0xF31CE, 32);
          Serial.println("Volume Down");
          delay(200);
          irrecv.enableIRIn();
          break;  


   
          case 0x70B16959: //Zero Keypad Button
        // Toggle Stepper up or down
        if(togglestate==0){
        digitalWrite(EnablePin, LOW);
        togglestate=1;
        Serial.println(togglestate);
        Serial.println("  LOWERING SCREEN");  


        // Activate Stepper Motor
          // Set the spinning direction counterclockwise:
          digitalWrite(dirPin, LOW);
        

          for (int i = 0; i < (Rotations*0.5)*stepsPerRevolution; i++) {
            // These four lines result in 1 step:
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(500);
          }
          for (int i = 0; i < (Rotations*0.5)*stepsPerRevolution; i++) {
            // These four lines result in 1 step:
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(500);
          }          
          
          digitalWrite(EnablePin, HIGH);
          Serial.println("  COMPLETE");      
        }


        
        else {
        digitalWrite(EnablePin, LOW);
        togglestate=0;
        Serial.println(togglestate);
        Serial.println("  RAISING SCREEN");    

        // Activate Stepper Motor
          digitalWrite(dirPin, HIGH);
        
          
          for (int i = 0; i < (Rotations*0.5)*stepsPerRevolution; i++) {
            // These four lines result in 1 step:
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(500);
          }
          for (int i = 0; i < (Rotations*0.5)*stepsPerRevolution; i++) {
            // These four lines result in 1 step:
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(500);
          }
          digitalWrite(EnablePin, HIGH);
          Serial.println("  COMPLETE");        

        
        }
        break;
        
    }
    irrecv.resume(); 
  }

}
