
// Coreography with wires 
#include <Servo.h>

#define LEFT_PIN 9
#define RIGHT_PIN 10
#define BOW_PIN 11
#define RIGHT_ARM 12

#define LEFT_STRETCHED_POSITION 30
#define LEFT_REST_POSITION 180

#define RIGHT_STRETCHED_POSITION 30
#define RIGHT_REST_POSITION 180

#define BOW_STRETCHED_POSITION 160
#define BOW_REST_POSITION 90

#define RARM_HIGH_POSITION 0
#define RARM_LOW_POSITION 90

#define tempo 7

Servo leftMotor, rightMotor, bowMotor, rarmMotor;

void setup() {
    leftMotor.attach(LEFT_PIN);
    rightMotor.attach(RIGHT_PIN);
    bowMotor.attach(BOW_PIN);
    rarmMotor.attach(RIGHT_ARM);
    
    leftMotor.write(LEFT_REST_POSITION);
    rightMotor.write(RIGHT_REST_POSITION);
    bowMotor.write(BOW_REST_POSITION);   
    rarmMotor.write(LEFT_REST_POSITION);
}


void loop() {

    
    for(int i=LEFT_REST_POSITION;i>LEFT_STRETCHED_POSITION;i--){
    leftMotor.write(i);
    
    
    delay(tempo);
    }
   
    for(int i=LEFT_STRETCHED_POSITION;i<LEFT_REST_POSITION;i++){
    leftMotor.write(i);

    delay(tempo);
    }
   // delay(1000);
    
    for(int i=RIGHT_REST_POSITION;i>RIGHT_STRETCHED_POSITION;i--){
    rightMotor.write(i);
    rarmMotor.write(i/2.5);
    delay(tempo);
    }
    for(int i=RIGHT_STRETCHED_POSITION;i<RIGHT_REST_POSITION;i++){
    rightMotor.write(i);
    rarmMotor.write(i/2.5);
    delay(tempo);
    }
   // delay(1000);

    for(int i=BOW_REST_POSITION;i<BOW_STRETCHED_POSITION;i++){
    bowMotor.write(i);
    delay(15);
    }
    delay(2500);
    for(int i=BOW_STRETCHED_POSITION;i>BOW_REST_POSITION;i--){
    bowMotor.write(i);
    delay(10);
    }
    
        
//    delay(1000);
}



