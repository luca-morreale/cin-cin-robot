#include <NewPing.h>

// ---- SONAR DISTANCES DEBUGGING ----
#define DEBUG 1

// ---- SONAR PINS ----
#define TRIG_PIN_LEFT 2
#define ECHO_PIN_LEFT 3
#define TRIG_PIN_MIDDLE 4
#define ECHO_PIN_MIDDLE 5
#define TRIG_PIN_RIGHT 6
#define ECHO_PIN_RIGHT 7

#define MEASUREMENTS_NUMBER 30

// ---- SONAR PINS ----
#define TRIG_PIN_LEFT 2
#define ECHO_PIN_LEFT 3
#define TRIG_PIN_MIDDLE 4
#define ECHO_PIN_MIDDLE 5
#define TRIG_PIN_RIGHT 6
#define ECHO_PIN_RIGHT 7

// ---- MAXIMUM SONAR DISTANCE (CM) ----
#define MAX_DISTANCE 300

// ---- STOPPING DANCE DISTANCE (CM) ----
#define STOP_DISTANCE 130

// ---- SOMEONE DISTANCE (CM)
#define SOMEONE_DISTANCE 100

// ---- SONAR INITIALIZATION ----
long distanceLeft, distanceMiddle, distanceRight;
NewPing sonarLeft(TRIG_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE);
NewPing sonarMiddle(TRIG_PIN_MIDDLE, ECHO_PIN_MIDDLE, MAX_DISTANCE);
NewPing sonarRight(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);



void updateDistances()
{
  distanceRight = sonarRight.ping_cm();
  distanceRight = (distanceRight == 0) ? MAX_DISTANCE : distanceRight;

  distanceMiddle = sonarMiddle.ping_cm();
  distanceMiddle = (distanceMiddle == 0) ? MAX_DISTANCE : distanceMiddle;

  distanceLeft = sonarLeft.ping_cm();
  distanceLeft = (distanceLeft == 0) ? MAX_DISTANCE : distanceLeft;

  debug('R', distanceRight);
  debug('M', distanceMiddle);
  debug('L', distanceLeft);
}

void setup() {

  // Inizializzazione dei motori e dei vari componenti
  // Settaggio dei pin di OUTPUT ed INPUT
Serial.begin(9600);

  distanceLeft = 0;
  distanceMiddle = 0;
  distanceRight = 0;
}

void loop() {

 updateDistances();
 delay(100);
}

void debug(char description, long value)
{
#if DEBUG
  char buff[10];
  sprintf(buff, "%c %ld", description, value);
  debug(buff);
#endif
}

void debug(char *description, long value)
{
#if DEBUG
  char buff[50];
  sprintf(buff, "%s %ld", description, value);
  debug(buff);
#endif
}

void debug(char description, int value)
{
#if DEBUG
  char buff[20];
  sprintf(buff, "%c %d", description, value);
  debug(buff);
#endif
}

void debug(char *description, int value)
{
#if DEBUG
  char buff[50];
  sprintf(buff, "%s %d", description, value);
  debug(buff);
#endif
}

void debug(char *message)
{
#if DEBUG
  Serial.println(message);
#endif
}

