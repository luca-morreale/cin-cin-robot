
// Coreography with wires 
#include <Servo.h>

#define LEFT_PIN 9
#define RIGHT_PIN 10

#define LEFT_MIDDLE_POSITION 180
#define LEFT_STRETCHED_POSITION 0
#define LEFT_REST_POSITION 270

#define RIGHT_MIDDLE_POSITION 180
#define RIGHT_STRETCHED_POSITION 0
#define RIGHT_REST_POSITION 270

Servo leftMotor, rightMotor, bowMotor;

void setup() {
    leftMotor.attach(9);
    rightMotor.attach(10);
    bowMotor.attach(11);
    
    leftMotor.write(LEFT_MIDDLE_POSITION);
    rightMotor.write(RIGHT_MIDDLE_POSITION);
    
    bowMotor.write(5);
    
}


void loop() {
    
    leftMotor.write(LEFT_STRETCHED_POSITION);
    delay(1200);
    leftMotor.write(LEFT_REST_POSITION);
    delay(1200);
    
    rightMotor.write(RIGHT_STRETCHED_POSITION);
    delay(1500);
    rightMotor.write(RIGHT_REST_POSITION);
    delay(1500);
    
    bowMotor.write(170);
    delay(1500);
    bowMotor.write(5);
    delay(1500);
        
    delay(1000);
}




