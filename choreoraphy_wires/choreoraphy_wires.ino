
// Coreography with wires 
#include <Servo.h>

// ---- MOTOR PINS ----
#define LEFT_PIN 9
#define RIGHT_PIN 10
#define BOW_PIN 12
#define RIGHT_ARM 11
#define LEFT_ARM 52
#define ROTATION_PIN 8

// ---- MOTOR INITIAL & FINAL POSITIONS ----
#define LEFT_STRETCHED_POSITION 30
#define LEFT_REST_POSITION 180
#define RIGHT_STRETCHED_POSITION 30
#define RIGHT_REST_POSITION 180
#define BOW_STRETCHED_POSITION 200
#define BOW_REST_POSITION 90
#define RARM_STRETCHED_POSITION 70
#define RARM_REST_POSITION 10
#define LARM_STRETCHED_POSITION 70
#define LARM_REST_POSITION 10
#define ROTATION_REST_POSITION 10
#define ROTATION_STRETCHED_POSITION 100


#define tempo 5

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
    delay(1000);
    
    for(int i=RIGHT_REST_POSITION;i>RIGHT_STRETCHED_POSITION;i--){
    rightMotor.write(i);
    delay(tempo);
    }
    
    for(int i=RIGHT_STRETCHED_POSITION;i<RIGHT_REST_POSITION;i++){
    rightMotor.write(i);
    delay(tempo);
    }
   // delay(1000);

    
    
        
//    delay(1000);
}



