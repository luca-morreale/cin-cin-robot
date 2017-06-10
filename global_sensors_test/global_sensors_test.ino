/* IMPORTANTISSIMO: I SONAR VANNO ALIMENTATI A PARTE (5 V)
  Trigger -> Grigio
  Echo -> Viola
  Gnd -> Verde
  Vcc -> Blu
*/

// ---- LIBRARIES ----
#include <NewPing.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

// ---- Constants ----
#define TRUE true
#define FALSE false
#define ON 1
#define OFF 0

// ---- SONAR DISTANCES DEBUGGING ----
#define DEBUG 1

// ---- MOTOR PINS ----
#define LEFT_PIN 9
#define RIGHT_PIN 10
#define BOW_PIN 53
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

// ---- CAMERA's DEALYS ----
#define TURN_ON_DELAY 200
#define TURN_OFF_DELAY 4000
#define SHOOT_DELAY 500        // if increased will take a video!
#define SWITCH_STAGE_DELAY 200
#define WIFI_ON_DELAY 4000
#define WIFI_OFF_DELAY 4000

// ---- DELAYS ----
#define BOW_DOWN_DELAY 1500
#define BOW_UP_DELAY 800

// ---- SONAR PINS ----
#define TRIG_PIN_LEFT 2
#define ECHO_PIN_LEFT 3
#define TRIG_PIN_MIDDLE 4
#define ECHO_PIN_MIDDLE 5
#define TRIG_PIN_RIGHT 6
#define ECHO_PIN_RIGHT 7

#define MEASUREMENTS_NUMBER 30

// ---- MP3 PLAYER PINS ----
#define RXPIN 12
#define TXPIN 13

// ---- SONAR MINIMUM THRESHOLD (CM) ----
#define SONAR_MINIMUM_THRESHOLD 10

// ---- CAMERA's PINS ----
#define CAMERA_PIN 21
#define CAMERA_SHOT_PIN 20

// ---- TOUCH SENSOR PIN ----
#define TOUCH_SENSOR_PIN 14
 
// ---- MAXIMUM SONAR DISTANCE (CM) ----
#define MAX_DISTANCE 300

// ---- PHOTO RESISTOR THRESHOLD ----
#define PHOTO_RESISTOR_THRESHOLD 150

// ---- STOPPING DANCE DISTANCE (CM) ----
#define STOP_DISTANCE 130

// ---- SOMEONE DISTANCE (CM)
#define SOMEONE_DISTANCE 100

// ---- SONAR INITIALIZATION ----
long distanceLeft, distanceMiddle, distanceRight;
NewPing sonarLeft(TRIG_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE);
NewPing sonarMiddle(TRIG_PIN_MIDDLE, ECHO_PIN_MIDDLE, MAX_DISTANCE);
NewPing sonarRight(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);

// ---- MOTOR INITIALIZATION ----
Servo leftMotor, rightMotor, bowMotor, rarmMotor, larmMotor, rotationMotor;

// ---- MP3 PLAYER INITIALIZATION ----
SoftwareSerial mp3Serial(RXPIN, TXPIN);

// ---- STATE VARIABLES OF CAMERA ----
int camState = OFF;
int wifiState = OFF;

// ---- MARSUPIUM ANALOG PIN ----
int photoResistor = A0;

// ---- CONTROL VARIABLES ----
boolean someone = false; // booleano che indica la presenza o meno dell'utente
boolean engagement = false;
boolean mp3_stopper = false;


// ---- FUNCTION PROTOTYPES ----
void attachServos();
void initServos();
void initSerial();
void initAnalog();
void initTouch();
void initPinCamera();

void cin_cin_dance();
void cin_cin_engagement();
void cin_cin_menu();
void cin_cin_selfie();

void sayHi();
void playDanceMusic();
void greetClient();
void offerMenu();

void goBackFromLeft();
void goBackFromRight();

void bow();
void standup();
void rotateForSelfie();
void rotateBackFromSelfie();
void doSelfie();


void updateDistances();
boolean isClose();
boolean thereIsSomeone();
boolean thereIsMenu();
boolean isTouched();
boolean clientEngaged();

void turnCameraOn();
void turnCameraOff();
void takePicture();
void switchWifiOn();
void switchWifiOff();

void debug(char description, long value);
void debug(char *description, long value);
void debug(char description, int value);
void debug(char *description, int value);
void debug(char *message);


void setup() {

  // Inizializzazione dei motori e dei vari componenti
  // Settaggio dei pin di OUTPUT ed INPUT

    initSerial();

    initPinCamera();

    initAnalog();

    initTouch();
  
    distanceLeft = 0;
    distanceMiddle = 0;
    distanceRight = 0;
}


void initSerial()
{
  Serial.begin(9600);
  mp3Serial.begin(9600);
  mp3_set_serial (mp3Serial); //set Serial for DFPlayer-mini mp3 module
  mp3_set_volume (20); //max volume is 30
}

void initAnalog()
{
  pinMode(photoResistor, INPUT);// Set photoResistor - A0 pin as an input
}

void initTouch()
{
  pinMode (TOUCH_SENSOR_PIN, INPUT); 
}

void initPinCamera()
{
    pinMode(CAMERA_PIN, OUTPUT);
    pinMode(CAMERA_SHOT_PIN, OUTPUT);
    
    digitalWrite(CAMERA_PIN, HIGH);
    digitalWrite(CAMERA_SHOT_PIN, LOW);
}

void loop() {

  //cin_cin_dance();
  //cin_cin_engagement();
  //if (someone)
  //  cin_cin_menu();
  //if (someone)
  //  cin_cin_selfie();
  
  
  for (int i = 0; i < 30; i++)
      updateDistances();
  debug("Do touch");
  
}


void doSelfie()
{
    turnOnCamera();
    //la persona tocca il sensore touch
    while(!isTouched());
    takePicture();

    switchOnWiFi();
    delay(120000);
    switchOffWiFi();
    
    turnOffCamera();
}

void updateDistances()
{
  distanceRight = sonarRight.ping_cm();
  distanceRight = (distanceRight == 0 || distanceRight <= SONAR_MINIMUM_THRESHOLD) ? MAX_DISTANCE : distanceRight;

  distanceMiddle = sonarMiddle.ping_cm();
  distanceMiddle = (distanceMiddle == 0 || distanceMiddle <= SONAR_MINIMUM_THRESHOLD) ? MAX_DISTANCE : distanceMiddle;

  distanceLeft = sonarLeft.ping_cm();
  distanceLeft = (distanceLeft == 0 || distanceLeft <= SONAR_MINIMUM_THRESHOLD) ? MAX_DISTANCE : distanceLeft;

  debug('R', distanceRight);
  debug('M', distanceMiddle);
  debug('L', distanceLeft);
}

boolean isClose()
{
  return distanceRight < STOP_DISTANCE || distanceMiddle < STOP_DISTANCE || distanceLeft < STOP_DISTANCE;
}

boolean thereIsMenu()
{
  int analog_value = 0;
  analog_value = analogRead(photoResistor);
  debug("Light: ",analog_value);
  if (analog_value > PHOTO_RESISTOR_THRESHOLD)
      return false;
  return true;
}

boolean isTouched()
{
  int touch_value = 0;
  touch_value = digitalRead(TOUCH_SENSOR_PIN);
  if (touch_value == HIGH)
    return true;
  return false;
}

boolean thereIsSomeone()
{
  updateDistances();

  if (isClose()) {
    someone = TRUE;
  } else {
    someone = FALSE;
  }
  return someone;
}

void turnOnCamera()
{
    if (camState == OFF) {
        digitalWrite(CAMERA_PIN, LOW);
        delay(TURN_ON_DELAY);
        digitalWrite(CAMERA_PIN, HIGH);
        delay(5000);    // wait it turns on
        camState = ON;
    }
}

void turnOffCamera()
{
    if (camState == ON) {
        digitalWrite(CAMERA_PIN, LOW);
        delay(TURN_OFF_DELAY);
        digitalWrite(CAMERA_PIN, HIGH);
        
        camState = OFF;
    }
}


void takePicture()
{
    if (camState == ON) {
        switchToPictureStage();
        digitalWrite(CAMERA_SHOT_PIN, HIGH);
        delay(SHOOT_DELAY);
        digitalWrite(CAMERA_SHOT_PIN, LOW);
        delay(SHOOT_DELAY);
    }
}

void switchToPictureStage()
{
    for (int i = 0; i < 2; i++) {
        digitalWrite(CAMERA_PIN, LOW);
        delay(SWITCH_STAGE_DELAY);
        digitalWrite(CAMERA_PIN, HIGH);
        delay(SWITCH_STAGE_DELAY);
    }
}

void switchOnWiFi()
{
    if (camState == ON && wifiState == OFF) {
        digitalWrite(CAMERA_SHOT_PIN, HIGH);
        delay(WIFI_ON_DELAY);
        digitalWrite(CAMERA_SHOT_PIN, LOW);
        
        wifiState = ON;
    }
}

void switchOffWiFi()
{
    if (camState == ON && wifiState == ON) {
        digitalWrite(CAMERA_SHOT_PIN, HIGH);
        delay(WIFI_OFF_DELAY);
        digitalWrite(CAMERA_SHOT_PIN, LOW);
        
        wifiState = OFF;
    }
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

