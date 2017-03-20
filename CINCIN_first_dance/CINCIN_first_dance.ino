
// CINCIN first dance (readable version)
// rotate when distance is more than 60 cm
// move laterally when is below 20 cm

#include <Servo.h>

#define DEBUG 1
#define NUM_READINGS 3
#define BOUD_RATE 9600

#define LATERAL_MOTOR_PIN 10
#define ROTATION_MOTOR_PIN 9
#define SIGNAL_PIN 6

#define LOW_DISTANCE 20
#define FAR_DISTANCE 60

#define DEALY_STILL 50
#define DEALY_DEGREE_MOVEMENTS 10

#define ANGLE_LEFT_ROTATION 30
#define ANGLE_START_ROTATION 102
#define ANGLE_RIGHT_ROTATION 175

#define ANGLE_START_BOW 1500
#define ANGLE_REST_BOW 500
#define ANGLE_END_BOW 2500

Servo lateralMotor;
Servo rotationMotor;

int currentIndex;
float distances[NUM_READINGS];
float totalDistance;

int lateralAngle;
int rotationAngle;

void setup() {
  Serial.begin(9600);

  currentIndex = 0;
  clearTotal();
  clearDistances();
  lateralAngle = 0;
  rotationAngle = 0;

  lateralMotor.attach(LATERAL_MOTOR_PIN);
  rotationMotor.attach(ROTATION_MOTOR_PIN);
  initMotors();
}

void initMotors()
{
  rotationMotor.write(ANGLE_START_ROTATION);
  lateralMotor.writeMicroseconds(ANGLE_START_BOW);
}

void loop() {
  float distance = getDistance();

  removeFirstDistance();
  shiftDistances();
  
  totalDistance += distance;
  appendDistance(distance);

  if (isTooFar()) {
    clearTotal();
    clearDistances();
  } else {
    performBehavior(averageDistance());
  }
}

float averageDistance()
{
  return totalDistance / NUM_READINGS;
}

void removeFirstDistance()
{
  totalDistance -= distances[0];
}

void shiftDistances()
{
  for (int i=0; i < NUM_READINGS-1; i++) {
    distances[i] = distances[i + 1];
  }
  distances[NUM_READINGS - 1] = 0;
}

void appendDistance(float distance)
{
  distances[currentIndex++] = distance;
  if (currentIndex >= NUM_READINGS) {
    currentIndex = NUM_READINGS - 1;
  }
}

int isTooFar()
{
  return getDistanceFromEnd(0) == 0 && getDistanceFromEnd(1) == 0;
}

float getDistanceFromEnd(int position)
{
  return (currentIndex-position > 0)? distances[currentIndex-position] : 0;
}

void performBehavior(float avgDistance)
{
  if (avgDistance < LOW_DISTANCE) {
    //stopMovements();
    moveLaterally();
  } else if (avgDistance > LOW_DISTANCE && avgDistance < FAR_DISTANCE) {
    //moveLaterally();
  } else {  // if (avgDistance > FAR_DISTANCE) 
    rotate();
 }
 debugDistance(avgDistance);
}

void stopMovements()
{
  // do nothing, keep it still
  delay(DEALY_STILL);
}

void moveLaterally()
{
  reachAngle360(&lateralMotor, lateralAngle, ANGLE_REST_BOW);
  lateralAngle = ANGLE_START_BOW;
  reachAngle360(&lateralMotor, lateralAngle, ANGLE_END_BOW);
  lateralAngle = ANGLE_END_BOW;
}

void rotate()
{
  reachAngle(&rotationMotor, rotationAngle, ANGLE_LEFT_ROTATION);
  rotationAngle = ANGLE_LEFT_ROTATION;
  reachAngle(&rotationMotor, rotationAngle, ANGLE_RIGHT_ROTATION);
  rotationAngle = ANGLE_RIGHT_ROTATION;
  reachAngle(&rotationMotor, rotationAngle, ANGLE_START_ROTATION);
  rotationAngle = ANGLE_START_ROTATION;
}

void reachAngle360(Servo *motor, int startingAngle, int angle)
{
  motor->writeMicroseconds(angle);
  delay(1000);
}

void reachAngle(Servo *motor, int startingAngle, int angle)
{
  for(int i = startingAngle; cycleCondition(i, angle, startingAngle); (startingAngle < angle)?i++:i--) {
    motor->write(i);
    delay(DEALY_DEGREE_MOVEMENTS);
  }
}

int cycleCondition(int i, int target_degree, int start_degree)
{
  if (target_degree > start_degree) {
    return i < target_degree;
  } else {
    return i > target_degree;
  }
}


void debugDistance(float avgDistance)
{
  if (DEBUG) {
    Serial.println(avgDistance);
  }
}

float getDistance()
{
  // durata dell'impulso
  float pulseTime;
  float distanza;

  pinMode(SIGNAL_PIN, OUTPUT);
  digitalWrite(SIGNAL_PIN, LOW);      // viene posto a LOW pin
  delayMicroseconds(2);              // per 2 microsecondi
  digitalWrite(SIGNAL_PIN, HIGH);     // invia un impulso di trigger
  delayMicroseconds(10);             // di 10 microsecondi
  digitalWrite(SIGNAL_PIN, LOW);      // pone il pin al LOW in attesa che l'impulso torni indietro

  pinMode(SIGNAL_PIN, INPUT);
  pulseTime = pulseIn(SIGNAL_PIN, HIGH); // legge l'eco dell'impulso emesso in microsecondi
  return pulseTime / 58;            // divide la durata per 58 per ottenere la distanza in cm
}

void clearTotal()
{
 totalDistance = 0;
}

void clearDistances()
{
  for (int i=0; i<NUM_READINGS; i++) {
    distances[i] = 0;
  }
}


