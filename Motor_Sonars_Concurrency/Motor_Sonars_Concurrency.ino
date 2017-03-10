#include <NewPing.h>
#include <Servo.h>

#define LEFT_PIN 9
#define LEFT_MIDDLE_POSITION 180
#define LEFT_STRETCHED_POSITION 0
#define LEFT_REST_POSITION 270

#define trigPinLeft 2
#define echoPinLeft 3
#define trigPinMiddle 4
#define echoPinMiddle 5
#define trigPinRight 6
#define echoPinRight 7
#define maxDistance 300

long distanceLeft,distanceMiddle,distanceRight;
NewPing sonarLeft(trigPinLeft, echoPinLeft, maxDistance);
NewPing sonarMiddle(trigPinMiddle, echoPinMiddle, maxDistance);
NewPing sonarRight(trigPinRight, echoPinRight, maxDistance);
Servo leftMotor;
int stop = 0;

void setup() {
  Serial.begin(9600);
  distanceLeft = 0;
  distanceMiddle = 0;
  distanceRight = 0;
  leftMotor.attach(9);
  leftMotor.write(LEFT_MIDDLE_POSITION);
}

void loop() {

  cin_cin_dance();

}

void cin_cin_dance() {

  if(!stop){
    leftMotor.write(LEFT_STRETCHED_POSITION);
    getDistance();
    if(distanceLeft != 0 || distanceMiddle != 0 || distanceRight != 0)
      stop = 1;
    delay(700);
  }
  else{
    getDistance();
    if(distanceLeft == 0 && distanceMiddle == 0 && distanceRight == 0)
      stop = 0;
  }

  if(!stop){
    leftMotor.write(LEFT_REST_POSITION);
    getDistance();
    if(distanceLeft != 0 || distanceMiddle != 0 || distanceRight != 0)
      stop = 1;
    delay(700);
  }
  else{
    getDistance();
    if(distanceLeft == 0 && distanceMiddle == 0 && distanceRight == 0)
      stop = 0;
  }
}

void getDistance()
{
  distanceLeft = sonarLeft.ping_cm();
  distanceMiddle = sonarMiddle.ping_cm();
  distanceRight = sonarRight.ping_cm();
  Serial.print("Left Sonar detects ");
  Serial.print(distanceLeft);
  Serial.println(" cm");
  Serial.print("Middle Sonar detects ");
  Serial.print(distanceMiddle);
  Serial.println(" cm");
  Serial.print("Right Sonar detects ");
  Serial.print(distanceRight);
  Serial.println(" cm");
  Serial.println("");
  Serial.println("");
}

