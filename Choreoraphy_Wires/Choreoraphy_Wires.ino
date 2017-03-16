
// Coreography with wires 
#include <Servo.h>

#define LEFT_PIN 9
#define RIGHT_PIN 10
#define BOW_PIN 11

#define LEFT_STRETCHED_POSITION 10
#define LEFT_REST_POSITION 180

#define RIGHT_STRETCHED_POSITION 10
#define RIGHT_REST_POSITION 180

#define BOW_STRETCHED_POSITION 160
#define BOW_REST_POSITION 90

Servo leftMotor, rightMotor, bowMotor;

void setup() {
    leftMotor.attach(LEFT_PIN);
    rightMotor.attach(RIGHT_PIN);
    bowMotor.attach(BOW_PIN);
    
    leftMotor.write(LEFT_REST_POSITION);
    rightMotor.write(RIGHT_REST_POSITION);
    bowMotor.write(BOW_REST_POSITION);   
}


void loop() {
    
    leftMotor.write(LEFT_STRETCHED_POSITION);
    delay(1000);
    leftMotor.write(LEFT_REST_POSITION);
    delay(1000);
    
    rightMotor.write(RIGHT_STRETCHED_POSITION);
    delay(1000);
    rightMotor.write(RIGHT_REST_POSITION);
    delay(1000);
    
    bowMotor.write(BOW_STRETCHED_POSITION);
    delay(5000);
    bowMotor.write(BOW_REST_POSITION);
    delay(1500);
        
    delay(1000);
}



