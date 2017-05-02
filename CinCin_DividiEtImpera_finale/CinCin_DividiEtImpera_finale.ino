/* IMPORTANTISSIMO: I SONAR VANNO ALIMENTATI A PARTE (5 V)
  Trigger -> Grigio
  Echo -> Viola
  Gnd -> Verde
  Vcc -> Blu
*/

/*
  mp3 player: blu 13, verde 12
  motori: giallo 11, blu 10, rosso 9, beige 8, grigio 16, arancione 15
  sonar: arancione scuro 7, verde associato 6, arancione più chiaro 5, verde associato 4, beige 3, verde associato 2
  camera: blu 19, viola 20
  fotoresistenza: blu A0
  
  breadboard-breadboard:
    sonar: grigio GROUND, viola TENSIONE 
    motori: beige GROUND, blu TENSIONE ...
    
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
#define BOW_PIN 15
#define RIGHT_ARM 11
#define LEFT_ARM 16
#define ROTATION_PIN 8

// ---- MOTOR INITIAL & FINAL POSITIONS ----
#define LEFT_STRETCHED_POSITION 30
#define LEFT_REST_POSITION 180
#define RIGHT_STRETCHED_POSITION 30
#define RIGHT_REST_POSITION 180
#define BOW_STRETCHED_POSITION 190
#define BOW_REST_POSITION 90
#define RARM_STRETCHED_POSITION 10
#define RARM_REST_POSITION 60
#define LARM_STRETCHED_POSITION 120
#define LARM_REST_POSITION 90
#define ROTATION_REST_POSITION 10
#define ROTATION_STRETCHED_POSITION 100

// ---- CAMERA's DEALYS ----
#define TURN_ON_DELAY 200
#define TURN_OFF_DELAY 4000
#define SHOOT_DELAY 500        // if increased will take a video!
#define SWITCH_STAGE_DELAY 500
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

// ---- SONAR PINS ----
#define TRIG_PIN_LEFT 2
#define ECHO_PIN_LEFT 3
#define TRIG_PIN_MIDDLE 4
#define ECHO_PIN_MIDDLE 5
#define TRIG_PIN_RIGHT 6
#define ECHO_PIN_RIGHT 7

// ---- SONAR MINIMUM THRESHOLD (CM) ----
#define SONAR_MINIMUM_THRESHOLD 10

// ---- CAMERA's PINS ----
#define CAMERA_PIN 20
#define CAMERA_SHOT_PIN 19

// ---- TOUCH SENSOR PIN ----
#define TOUCH_SENSOR_PIN 14

// ---- MAXIMUM SONAR DISTANCE (CM) ----
#define MAX_DISTANCE 300

// ---- PHOTO RESISTOR THRESHOLD ----
#define PHOTO_RESISTOR_THRESHOLD 15

// ---- STOPPING DANCE DISTANCE (CM) ----
#define STOP_DISTANCE 80

// ---- SOMEONE DISTANCE (CM)
#define SOMEONE_DISTANCE 80

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
boolean touched = false;
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
void forgottenMenu();
void sponsorMenu();
void proposeSelfie();
void explainSelfie();
void cheese();
void discount();
void sayBye();
void sayHiChinese();
void cmon();
void credits();

void goBackFromLeft();
void goBackFromRight();

void bow();
void standup();
void rotateForSelfie();
void rotateBackFromSelfie();
void doSelfie();
void pullUpLeftArm();
void pullDownLeftArm();

void updateDistances();
boolean isClose();
boolean thereIsSomeone();
boolean thereIsMenu();
boolean isTouched();
boolean clientEngaged();

void turnOnCamera();
void turnOffCamera();
void takePicture();
void switchOnWiFi();
void switchOffWiFi();

void debug(char description, long value);
void debug(char *description, long value);
void debug(char description, int value);
void debug(char *description, int value);
void debug(char *message);


void setup() {

  // Inizializzazione dei motori e dei vari componenti
  // Settaggio dei pin di OUTPUT ed INPUT

  attachServos();

  initServos();

  initSerial();

  initPinCamera();

  initAnalog();

  initTouch();

  distanceLeft = 0;
  distanceMiddle = 0;
  distanceRight = 0;

  camState = ON;
  turnOffCamera();
}

void attachServos()
{
  leftMotor.attach(LEFT_PIN);
  rightMotor.attach(RIGHT_PIN);
  bowMotor.attach(BOW_PIN);
  rarmMotor.attach(RIGHT_ARM);
  larmMotor.attach(LEFT_ARM);
  rotationMotor.attach(ROTATION_PIN);
}

void initServos()
{
  leftMotor.write(LEFT_REST_POSITION);
  rightMotor.write(RIGHT_REST_POSITION);
  bowMotor.write(BOW_REST_POSITION);
  rarmMotor.write(RARM_REST_POSITION);
  larmMotor.write(LARM_REST_POSITION);
  rotationMotor.write(ROTATION_REST_POSITION);
}

void initSerial()
{
  Serial.begin(9600);
  mp3Serial.begin(9600);
  mp3_set_serial (mp3Serial); //set Serial for DFPlayer-mini mp3 module
  mp3_set_volume (30); //max volume is 30
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

  cin_cin_dance();
  cin_cin_engagement();
  if (someone)
    cin_cin_menu();
  if (someone)
    cin_cin_selfie();
}

void cin_cin_dance() {

  // Funzione che fa ballare Cin Cin con musica cinese di sottofondo
  // Mentre balla rileva se passa qualcuno entro 2 metri c.a.
  // Quando rileva qualcuno si fermano i motori, la musica e la funzione ritorna dopo aver settato il flag someone a TRUE

  someone = false;

  if (thereIsSomeone()) {
    return;
  }

  while (true) {

    playDanceMusic();

    for (int i = LEFT_REST_POSITION; i >= LEFT_STRETCHED_POSITION; i--) {
      leftMotor.write(i);
      if ((LEFT_REST_POSITION - i) % 10 == 0) {
        if (thereIsSomeone()) {
          goBackFromLeft();
          return;
        }
      }
    }

    for (int i = LEFT_STRETCHED_POSITION; i < LEFT_REST_POSITION; i++) {
      leftMotor.write(i);
      if ((i - LEFT_STRETCHED_POSITION) % 10 == 0) {
        if (thereIsSomeone()) {
          goBackFromLeft();
          return;
        }
      }
    }

    for (int i = RIGHT_REST_POSITION; i >= RIGHT_STRETCHED_POSITION; i--) {
      rightMotor.write(i);
      if ((RIGHT_REST_POSITION - i) % 10 == 0) {
        if (thereIsSomeone()) {
          goBackFromRight();
          return;
        }
      }
    }

    for (int i = RIGHT_STRETCHED_POSITION; i < RIGHT_REST_POSITION; i++) {
      rightMotor.write(i);
      if ((i - RIGHT_STRETCHED_POSITION) % 10 == 0) {
        if (thereIsSomeone()) {
          goBackFromRight();
          return;
        }
      }
    }
  }

}

void cin_cin_engagement()
{
  engagement = false;
  sayHi();  // contains delay
  sayHiChinese();
  switchOffWiFi();

  int i = 0;
  while (i < 5 && !engagement) {
    if (thereIsSomeone()) {
      bow();
      standup();
      greetClient();
      engagement = true;
    }
    i++;
  }
}

void cin_cin_menu() {

  // Funzione che fa presentare il ristorante e offrire il menù all'utente
  // Cin Cin presenta il ristorante all'utente per poi invitarlo a dare un'occhiata al menÃ¹ facendo un inchino
  // Se l'utente non prende il menÃ¹ allora Cin Cin si rialza e verifica che l'utente sia ancora lÃ¬, ed eventualmente setta il flag someone a FALSE prima di ritornare
  // Se l'utente Ã¨ ancora lÃ¬ riprova ad offrirgli il menÃ¹, se non viene preso nemmeno questa volta la funzione ritorna
  // Se l'utente prende il menÃ¹ Cin Cin resta inchinato fino a che non viene rimesso a posto, per poi ritornare dopo aver eventualmente settato il flag someone

  engagement = false;

  int i = 0;
  while (i < 5 && !engagement) {
    if (thereIsSomeone()) {
      offerMenu();
      engagement = true;
    }
    i++;
  }

  if (engagement) {
    delay(3000);
    if (!thereIsMenu()) {
      for (int k = 0; k < 200; k++)
      {
        if (thereIsMenu())
          k = 200;
        else
          delay(100);
        if (k == 199) {
          forgottenMenu();
          delay(2000);
        }
      }
      sponsorMenu();
    }
    else {
      offerMenu();
      delay(3000);
      if (!thereIsMenu()) {
        for (int w = 0; w < 200; w++)
        {
          if (thereIsMenu())
            w = 200;
          else
            delay(100);
          if (w == 199) {
            forgottenMenu();
            delay(2000);
          }
        }
        sponsorMenu();
      }
    }
  }
}

void cin_cin_selfie()
{
  engagement = FALSE;
  turnOnCamera();
  int i = 0;
  //rotazione cin cin a 80°
  while (i < 5 && !clientEngaged()) {
    if (thereIsSomeone()) {
      proposeSelfie();
      rotateForSelfie();
      doSelfie();
      rotateBackFromSelfie();
      if (touched)
        discount();
      engagement = TRUE;
      switchOnWiFi();
    }
    i++;
  }
  if (engagement) {
    sayBye();
    for (int z = 0; z < 40; z++)
    {
      if (isTouched()) {
        z = 40;
        credits();
      }
      else
        delay(100);
    }
    pullDownLeftArm();
  }
}

// -------------- HELPER FUNCTIONS --------------

void playDanceMusic()
{
  if (!mp3_stopper) {
    mp3_play(1); // play 0001.mp3
    mp3_single_loop(true);
    mp3_stopper = true;
    delay(3000);
  }
}

void sayHi()
{
  mp3_play(2); //"EHI EHI VIENI QUI!!!
  delay(3000);
}

void greetClient()
{
  mp3_play(3); //"(inchino) PIACERE DI CONOSCERTI, IO SONO CIN CIN"
  delay(4000);
}

void offerMenu()
{
  mp3_play(4); //"VUOI GUARDARE IL MENU' DEL NOSTRO RISTORANTE? PRENDILO DAL MARSUPIO!"
  delay(6000);
}

void sponsorMenu()
{
  mp3_play(5); //"HAI VISTO CHE PIATTI BUONI CHE ABBIAMO?"
  delay(3000);
}

void proposeSelfie()
{
  mp3_play(6); //"TI VA DI FARE UN SELFIE CON ME?"
  delay(2000);
}

void explainSelfie()
{
  mp3_play(7); //"BASTA CHE SCHIACCI IL CAPPELLO!"
  delay(3000);
}

void cheese()
{
  mp3_play(8); //"FAI CHEESEEEE!"
  delay(2000);
}

void discount()
{
  mp3_play(9); //"SIAMO VENUTI BENISSIMO!"
  delay(6000);
}

void sayBye()
{
  mp3_play(10); //"E' STATO UN PIACERE CONOSCERTI!"
  delay(4000);
}

void forgottenMenu()
{
  mp3_play(11); //"EHI NON SCAPPARE CON IL MENU'"
  delay(2000);
}

void cmon()
{
  mp3_play(12); //"DAI DAI SBRIGATI!"
  delay(3000);
}

void sayHiChinese()
{
  mp3_play(13); //"EHI EHI QUE GOLA EH?"
  delay(3000);
}

void credits()
{
  mp3_play(14); //"TI SCATTERO' UNA FOTO..."
  delay(32000);
}

void goBackFromLeft()
{
  leftMotor.write(LEFT_REST_POSITION);
  someone = true;
  delay(400);
  mp3_stop();
  mp3_stopper = false;
}

void goBackFromRight()
{
  rightMotor.write(RIGHT_REST_POSITION);
  someone = true;
  delay(400);
  mp3_stop ();
  mp3_stopper = false;
}

void bow()
{
  for (int i = BOW_REST_POSITION; i < BOW_STRETCHED_POSITION; i++) {
    bowMotor.write(i);
    delay(7);
  }
  delay(1000);    // delay to let the motor reach the position
}

void standup() {
  for (int i = BOW_STRETCHED_POSITION; i > BOW_REST_POSITION; i--) {
    bowMotor.write(i);
    delay(7);
  }
  delay(1000);    // delay to let the motor reach the position
}

void rotateForSelfie()
{
  for (int i = ROTATION_REST_POSITION; i < ROTATION_STRETCHED_POSITION; i++) {
    rotationMotor.write(i);
    delay(5);
  }
}

void pullUpLeftArm()
{
  for (int i = LARM_REST_POSITION; i < LARM_STRETCHED_POSITION; i++) {
    larmMotor.write(i);
    delay(5);
  }
}

void pullDownLeftArm()
{
  for (int i = LARM_STRETCHED_POSITION; i > LARM_REST_POSITION; i--) {
    larmMotor.write(i);
    delay(5);
  }
}

void rotateBackFromSelfie()
{
  for (int i = ROTATION_STRETCHED_POSITION; i > ROTATION_REST_POSITION; i--) {
    rotationMotor.write(i);
    delay(5);
  }
}

void doSelfie()
{
  rarmMotor.write(RARM_STRETCHED_POSITION);
  delay(500);
  pullUpLeftArm();
  explainSelfie();
  //la persona tocca il sensore touch
  for (int k = 0; k < 80; k++)
  {
    if (isTouched()) {
      k = 80;
      cheese();
      takePicture();
      touched = true;
    }
    else
      delay(100);
    if (k == 79) {
      cmon();
      for (int j = 0; j < 60; j++)
      {
        if (isTouched()) {
          j = 60;
          cheese();
          takePicture();
          touched = true;
        }
        else
          delay(100);
      }
    }
  }
  rarmMotor.write(RARM_REST_POSITION);
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

boolean clientEngaged()
{
  return engagement;
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
  sprintf(buff, "%c%ld", description, value);
  debug(buff);
#endif
}

void debug(char *description, long value)
{
#if DEBUG
  char buff[50];
  sprintf(buff, "%s%ld", description, value);
  debug(buff);
#endif
}

void debug(char description, int value)
{
#if DEBUG
  char buff[20];
  sprintf(buff, "%c%d", description, value);
  debug(buff);
#endif
}

void debug(char *description, int value)
{
#if DEBUG
  char buff[50];
  sprintf(buff, "%s%d", description, value);
  debug(buff);
#endif
}

void debug(char *message)
{
#if DEBUG
  Serial.println(message);
#endif
}

