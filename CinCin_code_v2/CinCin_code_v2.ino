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
#define MAGIC_NUMBER 5

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
#define RARM_STRETCHED_POSITION 0
#define RARM_REST_POSITION 60
#define LARM_STRETCHED_POSITION 120
#define LARM_REST_POSITION 90
#define LARM_STRETCHED_POSITION_G 180
#define LARM_REST_POSITION_G 90
#define ROTATION_REST_POSITION 10
#define ROTATION_STRETCHED_POSITION 100

// ---- CAMERA's DEALYS ----
#define TURN_ON_DELAY 200
#define TURN_OFF_DELAY 4000
#define SHOOT_DELAY 500                // if increased will take a video!
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

// ---- TIMING VARIABLES ----
long audio_time = 0;



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
void gettingLaid();
void cheese();
void discount();
void sayBye();
void sayHiChinese();
void credits();
void pictureNoise();

bool motorMovement(Servo *motor, int start, int end, void(*goback)(void));
void motorMovementNoSonar(Servo *motor, int start, int end, void(*goback)(void));
bool forloopEndingCond(int i, int start, int end);
void forloopIncrement(int *i, int start, int end);
void goBackFromLeft();
void goBackFromRight();
void bow();
void standup();
void rotateForSelfie();
void rotateBackFromSelfie();
void doSelfie();
void pullUpLeftArm();
void pullDownLeftArm();
void pullUpLeftArmGesture();
void pullDownLeftArmGesture();
void convultionLeftArmWhileSpeak();
void danglingWhileSpeak();        // move the body while the robot is playing and audio
void dangleOnce();
void waitForMenu();
void selfieSequenceActions();
void hiddenFeature();
void putBackMotors();

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

long convertToMillis(int seconds);
void setAudioStopTime(int seconds);

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

void loop() 
{
    cin_cin_dance();
    cin_cin_engagement();
    if (thereIsSomeone()) {
        cin_cin_menu();
    }
    if (thereIsSomeone()) {
        cin_cin_selfie();
    }
}


void cin_cin_dance() {

    // Funzione che fa ballare Cin Cin con musica cinese di sottofondo
    // Mentre balla rileva se passa qualcuno entro 2 metri c.a.
    // Quando rileva qualcuno si fermano i motori, la musica e la funzione ritorna dopo aver settato il flag someone a TRUE

    someone = false;

    if (thereIsSomeone()) return; // in this case no need to attract someone

    while (true) {

        playDanceMusic();

        bool state = motorMovement(&rightMotor, RIGHT_REST_POSITION, RIGHT_STRETCHED_POSITION, &goBackFromRight);
        if (state) return;

        state = motorMovement(&rightMotor, RIGHT_STRETCHED_POSITION, RIGHT_REST_POSITION, &goBackFromRight);
        if (state) return;

        state = motorMovement(&leftMotor, LEFT_REST_POSITION, LEFT_STRETCHED_POSITION, &goBackFromLeft);
        if (state) return;

        state = motorMovement(&leftMotor, LEFT_STRETCHED_POSITION, LEFT_REST_POSITION, &goBackFromLeft);
        if (state) return;
    }
}

void cin_cin_engagement()
{
    engagement = false;
    sayHi();
    sayHiChinese();        // during presentation should rise the arm
    
    bow();
    standup();
    
    switchOffWiFi();

    int i = 0;
    while (i < MAGIC_NUMBER && !clientEngaged()) {
        if (thereIsSomeone()) {
            greetClient();
            engagement = true;
        }
        i++;
    }
}

void cin_cin_menu() 
{

    // Funzione che fa presentare il ristorante e offrire il menù all'utente
    // Cin Cin presenta il ristorante all'utente per poi invitarlo a dare un'occhiata al menÃ¹ facendo un inchino
    // Se l'utente non prende il menÃ¹ allora Cin Cin si rialza e verifica che l'utente sia ancora lÃ¬, ed eventualmente setta il flag someone a FALSE prima di ritornare
    // Se l'utente Ã¨ ancora lÃ¬ riprova ad offrirgli il menÃ¹, se non viene preso nemmeno questa volta la funzione ritorna
    // Se l'utente prende il menÃ¹ Cin Cin resta inchinato fino a che non viene rimesso a posto, per poi ritornare dopo aver eventualmente settato il flag someone

    engagement = false;

    int i = 0;
    while (i < MAGIC_NUMBER && !clientEngaged()) {
        if (thereIsSomeone()) {
            offerMenu();
            engagement = true;
        }
        i++;
    }
    if (!clientEngaged()) return;

    delay(500);     // WTF?!?! here it was delay 3000
    if (!thereIsMenu()) {
        waitForMenu();
    } else {
        offerMenu();
        delay(500);
        waitForMenu();
    }
    sponsorMenu();
}

void cin_cin_selfie()
{
    engagement = FALSE;
    turnOnCamera();
    int i = 0;
    //rotazione cin cin a 80°
    while (i < MAGIC_NUMBER && !clientEngaged()) {
        if (thereIsSomeone()) {
            selfieSequenceActions();
        }
        i++;
    }
}

// -------------- AUDIO FUNCTIONS --------------
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
    
    setAudioStopTime(3);
    convultionLeftArmWhileSpeak();
}

void greetClient()
{
    mp3_play(3); //"(inchino) PIACERE DI CONOSCERTI, IO SONO CIN CIN"
    
    setAudioStopTime(4);
    convultionLeftArmWhileSpeak();      // should also dangle???
}

void offerMenu()
{
    mp3_play(4); //"VUOI GUARDARE IL MENU' DEL NOSTRO RISTORANTE? PRENDILO DAL MARSUPIO!"

    setAudioStopTime(4);
    danglingWhileSpeak();
}

void sponsorMenu()
{
    mp3_play(5); //"HAI VISTO CHE PIATTI BUONI CHE ABBIAMO?"
    
    setAudioStopTime(3);
    danglingWhileSpeak();
}

void proposeSelfie()
{
    mp3_play(6); //"TI VA DI FARE UN SELFIE CON ME?"
    
    setAudioStopTime(2);
    convultionLeftArmWhileSpeak();
}

void gettingLaid()
{
    mp3_play(7); //"DAI METTITI IN POSA!"
    delay(3000);
}

void cheese()
{
    mp3_play(8); //"3..2..1..FAI CHEESE!"
    delay(5000);
}

void discount()
{
    mp3_play(9); //"SIAMO VENUTI BENISSIMO!"
    
    setAudioStopTime(6);
    danglingWhileSpeak();
}

void sayBye()
{
    mp3_play(10); //"E' STATO UN PIACERE CONOSCERTI!"
    
    setAudioStopTime(4);
    danglingWhileSpeak();
}

void forgottenMenu()
{
    mp3_play(11); //"EHI NON SCAPPARE CON IL MENU'"
    
    setAudioStopTime(2);
    danglingWhileSpeak();
}

void sayHiChinese()
{
    mp3_play(13); //"EHI EHI QUE GOLA EH?"

    setAudioStopTime(3);
    convultionLeftArmWhileSpeak();
}

void credits()
{
    mp3_play(14); //"TI SCATTERO' UNA FOTO..."
    
    setAudioStopTime(32);
    danglingWhileSpeak();
}

void pictureNoise()
{
    mp3_play(15); //"CHACK!"
    delay(2000);
}


// -------------- MOTOR FUNCTIONS --------------

// typedef void(*MotorRetreatFunction)(void);  // at the moment arduino does not support function pointer
bool motorMovement(Servo *motor, int start, int end, void(*goback)(void))
{
    for (int i = start; forloopEndingCond(i, start, end); forloopIncrement(&i, start, end)) {
        motor->write(i);
        if (abs(start - i) % 10 == 0) {
            if (thereIsSomeone()) {
                goback();
                return true;
            }
        }
    }
    return false;
}

void motorMovementNoSonar(Servo *motor, int start, int end, void(*goback)(void))
{
    for (int i = start; forloopEndingCond(i, start, end); forloopIncrement(&i, start, end)) {
        motor->write(i);
        delay(5);
    }
}

bool forloopEndingCond(int i, int start, int end)
{
    if (start > end) {
        return i > end;
    } 
    return i < start;
}

void forloopIncrement(int *i, int start, int end)
{
    if (start > end) {
        (*i)--;
    } else {
        (*i)++;
    }
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
    delay(1000);        // delay to let the motor reach the position
}

void standup() 
{
    for (int i = BOW_STRETCHED_POSITION; i > BOW_REST_POSITION; i--) {
        bowMotor.write(i);
        delay(7);
    }
    delay(1000);        // delay to let the motor reach the position
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

void pullUpLeftArmGesture()
{
    for (int i = LARM_REST_POSITION_G; i < LARM_STRETCHED_POSITION_G; i++) {
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

void pullDownLeftArmGesture()
{
    for (int i = LARM_STRETCHED_POSITION_G; i > LARM_REST_POSITION_G; i--) {
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
    gettingLaid();
    delay(3000);    // gives time to person to reach position
    cheese();
    takePicture();
    rarmMotor.write(RARM_REST_POSITION);
}

void convultionLeftArmWhileSpeak()
{
    long start = millis();
    long current = millis();

    while(current - start < audio_time){
        pullUpLeftArmGesture();
        delay(200);
        pullDownLeftArmGesture();
        current = millis();
    }
}

void danglingWhileSpeak()        // move the body while the robot is playing and audio
{
    long start = millis();
    long current = millis();

    while(current - start < audio_time){
        dangleOnce();
        current = millis();
    }
}

void dangleOnce()
{
    // please do not increase the delay
    motorMovementNoSonar(&leftMotor, LEFT_REST_POSITION, LEFT_STRETCHED_POSITION-20, &goBackFromLeft);
    delay(10);
    motorMovementNoSonar(&leftMotor, LEFT_STRETCHED_POSITION-20, LEFT_REST_POSITION, &goBackFromLeft);
    delay(10);
    motorMovementNoSonar(&leftMotor, RIGHT_REST_POSITION, RIGHT_STRETCHED_POSITION, &goBackFromRight);
    delay(10);
    motorMovementNoSonar(&leftMotor, RIGHT_STRETCHED_POSITION, RIGHT_REST_POSITION, &goBackFromRight);
}

void waitForMenu() 
{
    for (int k = 0; k < 199; k++) {
        if (thereIsMenu()) return;
        delay(100);
    }

    if (!thereIsMenu()) {
        forgottenMenu();
        delay(1000);        // WHY???? do we really need this?
    }
}

void selfieSequenceActions()
{
    putBackMotors();
    
    proposeSelfie();
    rotateForSelfie();
    doSelfie();     // inside pullUpLeftArm()
    rotateBackFromSelfie();
    discount();
    engagement = TRUE;
    switchOnWiFi();

    if (clientEngaged()) {
        sayBye();
        hiddenFeature();
        pullDownLeftArm();
    }
}

void putBackMotors()
{
    leftMotor.write(LEFT_REST_POSITION);
    rightMotor.write(RIGHT_REST_POSITION);
    bowMotor.write(BOW_REST_POSITION);
    rarmMotor.write(RARM_REST_POSITION);
    larmMotor.write(LARM_REST_POSITION);
    rotationMotor.write(ROTATION_REST_POSITION);
}

void hiddenFeature()
{
    for (int z = 0; z < 40; z++) {
        if (isTouched()) {
            z = 40;
            credits();
        }
        else {
            delay(100);
        }
    }
}


// -------------- SENSOR FUNCTIONS --------------

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


// -------------- CAMERA FUNCTIONS --------------

void turnOnCamera()
{
    if (camState == OFF) {
        digitalWrite(CAMERA_PIN, LOW);
        delay(TURN_ON_DELAY);
        digitalWrite(CAMERA_PIN, HIGH);
        delay(5000);        // wait it turns on
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
        pictureNoise();
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

// -------------- HELPER FUNCTIONS --------------

long convertToMillis(int seconds)
{
    return (long)seconds * 1000;
}

void setAudioStopTime(int seconds)
{
    audio_time = convertToMillis(seconds);
}

// -------------- DEBUG FUNCTIONS --------------

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
