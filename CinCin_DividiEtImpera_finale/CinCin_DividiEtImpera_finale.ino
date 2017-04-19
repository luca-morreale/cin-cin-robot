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

// ---- MOTOR PINS ----
#define LEFT_PIN 9
#define RIGHT_PIN 10
#define BOW_PIN 53
#define RIGHT_ARM 11
#define ROTATION_PIN 8

// ---- MOTOR INITIAL & FINAL POSITIONS ----
#define LEFT_STRETCHED_POSITION 30
#define LEFT_REST_POSITION 180
#define RIGHT_STRETCHED_POSITION 30
#define RIGHT_REST_POSITION 180
#define BOW_STRETCHED_POSITION 160
#define BOW_REST_POSITION 90
#define RARM_STRETCHED_POSITION 70
#define RARM_REST_POSITION 10
#define ROTATION_REST_POSITION 10
#define ROTATION_STRETCHED_POSITION 100

// ---- SONAR DISTANCES DEBUGGING ----
#define DEBUG 1


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


// ---- MOTOR INITIALIZATION ----
Servo leftMotor, rightMotor, bowMotor, rarmMotor, rotationMotor;


// ---- MP3 PLAYER INITIALIZATION ----
SoftwareSerial mp3Serial(RXPIN, TXPIN);


// ---- CONTROL VARIABLES ----
boolean someone = false; // booleano che indica la presenza o meno dell'utente
boolean engagement = false;
boolean mp3_stopper = false;

// ---- FUNCTION PROTOTYPES ----
void attachServos();
void initServos();
void initSerial();

void cin_cin_dance();
void cin_cin_engagement();
void cin_cin_menu();
void cin_cin_selfie();

void sayHi();
void playDanceMusic();
void greetClient();


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

    attachServos();
    initServos();
    
    initSerial();

    distanceLeft = 0;
    distanceMiddle = 0;
    distanceRight = 0;
}

void attachServos()
{
    leftMotor.attach(LEFT_PIN);
    rightMotor.attach(RIGHT_PIN);
    bowMotor.attach(BOW_PIN);
    rarmMotor.attach(RIGHT_ARM);
    rotationMotor.attach(ROTATION_PIN);
}

void initServos()
{
    leftMotor.write(LEFT_REST_POSITION);
    rightMotor.write(RIGHT_REST_POSITION);
    bowMotor.write(BOW_REST_POSITION);
    rarmMotor.write(RARM_REST_POSITION);
    rotationMotor.write(ROTATION_REST_POSITION);
}

void initSerial() 
{
    Serial.begin(9600);
    mp3Serial.begin(9600);
    mp3_set_serial (mp3Serial); //set Serial for DFPlayer-mini mp3 module
    mp3_set_volume (30); //max volume is 30
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
    
    if(thereIsSomeone()) {
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
    sayHi();

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
}

void cin_cin_selfie() 
{
    engagement = FALSE;
    int i = 0;
    //rotazione cin cin a 80°
    while (i < 5 && !clientEngaged()) {
        if (thereIsSomeone()) {
            rotateForSelfie();
            doSelfie();
            rotateBackFromSelfie();
            engagement = TRUE;
        }
        i++;
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
    delay(1500);
    mp3_play(3); //"EHI EHI VIENI QUI!!!
    delay(3000);
}

void greetClient()
{
    mp3_play(4); //"(inchino) MOLTO PIACERE DI CONOSCERTI, IO SONO CIN CIN"
    delay(4000);
    mp3_play(5); //"(inchino) MOLTO PIACERE DI CONOSCERTI, IO SONO CIN CIN"
    delay(4000);
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
    delay(2000);
    rarmMotor.write(RARM_REST_POSITION);
}



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

boolean isClose()
{
    return distanceRight < STOP_DISTANCE || distanceMiddle < STOP_DISTANCE || distanceLeft < STOP_DISTANCE;
}

boolean thereIsSomeone() 
{
    updateDistances();
    
    if (isClose()){
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

void turnCameraOn()
{ }
void turnCameraOff()
{ }
void takePicture()
{ }
void switchWifiOn()
{ }
void switchWifiOff()
{ }

void debug(char description, long value)
{
#ifndef DEBUG
    char buff[1s0];
    sprintf(buff, "%c%l", description, value);
    debug(buff);
#endif
}

void debug(char *description, long value)
{
#ifndef DEBUG
    char buff[50];
    sprintf(buff, "%s%l", description, value);
    debug(buff);
#endif
}

void debug(char description, int value)
{
#ifndef DEBUG
    char buff[20];
    sprintf(buff, "%c%d", description, value);
    debug(buff);
#endif
}

void debug(char *description, int value)
{
#ifndef DEBUG
    char buff[50];
    sprintf(buff, "%s%d", description, value);
    debug(buff);
#endif
}

void debug(char *message)
{
#ifndef DEBUG
    Serial.println(message);
#endif
}


