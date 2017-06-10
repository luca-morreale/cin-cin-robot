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

// ---- DEBUGGING FLAG ----
#define DEBUG 1

// ---- Constants ----
#define TRUE true
#define FALSE false
#define ON 1
#define OFF 0

// ---- MOTOR PINS ----
#define LEFT_PIN 9
#define RIGHT_PIN 10
#define BOW_PIN 11
#define RIGHT_ARM 12

// ---- MOTOR INITIAL & FINAL POSITIONS ----
#define LEFT_STRETCHED_POSITION 30
#define LEFT_REST_POSITION 180
#define RIGHT_STRETCHED_POSITION 30
#define RIGHT_REST_POSITION 180
#define BOW_STRETCHED_POSITION 160
#define BOW_REST_POSITION 90
#define RARM_HIGH_POSITION 0
#define RARM_LOW_POSITION 90

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


// ---- MAXIMUM SONAR DISTANCE (CM) ----
#define MAX_DISTANCE 300

// ---- STOPPING DANCE DISTANCE (CM) ----
#define STOP_DISTANCE 50

// ---- SONAR INITIALIZATION ---- 
long distanceLeft, distanceMiddle, distanceRight;
NewPing sonarLeft(TRIG_PIN_LEFT, ECHO_PIN_LEFT, MAX_DISTANCE);
NewPing sonarMiddle(TRIG_PIN_MIDDLE, ECHO_PIN_MIDDLE, MAX_DISTANCE);
NewPing sonarRight(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT, MAX_DISTANCE);


// ---- MOTOR INITIALIZATION ----
Servo leftMotor, rightMotor, bowMotor, rightArmMotor;


// ---- CONTROL VARIABLES ----
boolean clientPresence = false; // booleano che indica la presenza o meno dell'utente
boolean engagement = false;
boolean mp3_stopper = true; // in futuro forse non servirà, visto che quando viene rilevato qualcuno la funzione dance() ritorna



// ---- FUNCTION PROTOTYPES ----
void dance(); // Funzione che fa ballare Cin Cin con musica cinese di sottofondo

void cin_cin_engagement(); // Funzione che fa compiere la prima interazione con l'utente

void cin_cin_menu(); // Funzione che fa presentare il ristorante e offrire il menù all'utente

void cin_cin_selfie(); // Funzione che fa scattare un selfie con l'utente ed invia la foto in cassa tramite Wi-Fi

void selfie_rotation(); // Funzione che alza il braccio e fa ruotare Cin Cin per scattare il selfie

void debugDistance(long distance, char c); // Funzione che permette di stampare a video i valori rilevati dai sonar

void updateDistances(); // Funzione che aggiorna i valori rilevati dai sonar


void attachServos();           // attaches the servos to the respective pin
void initServos();             // sets the motors to the right position
boolean thereIsSomeone();      // updates the distances and sets respective boolean flag for the client's presence
boolean clientEngaged();       // returns true if any client has been engaged
void bowMotorDown();           // makes CIN-CIN bow
void bowMotorUp();             // makes CIN-CIN stands from the bow

void turnCameraOn();           // turns on the camera
void turnCameraOff();          // turns off the camera
void takePicture();            // takes a picture with the camera
void switchWifiOn();           // turns the wifi on
void switchWifiOff();          // turns the wifi off

void debug(char *message);     // prints a message on the serial
void debug(char description, long value);
void debug(char *description, long value);
void debug(char description, int value);
void debug(char *description, int value);

// ---- MP3 PLAYER INITIALIZATION ----
SoftwareSerial mySerial(RXPIN, TXPIN);


void setup() 
{
    // Inizializzazione dei motori e dei vari componenti
    // Settaggio dei pin di OUTPUT ed INPUT
    attachServos();
    initServos();

    Serial.begin(9600);
    mySerial.begin(9600);
    mp3_set_serial(mySerial); //set Serial for DFPlayer-mini mp3 module
    mp3_set_volume(20); //max volume is 30

    distanceLeft = 0;
    distanceMiddle = 0;
    distanceRight = 0;
}

void attachServos()
{
    leftMotor.attach(LEFT_PIN);
    rightMotor.attach(RIGHT_PIN);
    bowMotor.attach(BOW_PIN);
    rightArmMotor.attach(RIGHT_ARM);
}

void initServos()
{
    leftMotor.write(LEFT_REST_POSITION);
    rightMotor.write(RIGHT_REST_POSITION);
    bowMotor.write(BOW_REST_POSITION);   
    rightArmMotor.write(LEFT_REST_POSITION);
}

void loop() 
{
    dance();
    cin_cin_engagement();
    if (thereIsSomeone()) {
        cin_cin_menu();
    }
    if (thereIsSomeone()) {
        cin_cin_selfie();
    }
}

void dance() 
{
    // Funzione che fa ballare Cin Cin con musica cinese di sottofondo
    // Mentre balla rileva se passa qualcuno entro 2 metri c.a.
    // Quando rileva qualcuno si fermano i motori, la musica e la funzione ritorna dopo aver settato il flag someone a TRUE
    
    if(thereIsSomeone()) {
        return;
    }
    
    mp3_play (1); //play 0001.mp3

    while(true){
        if(!mp3_stopper){
          mp3_play (1); // play 0001.mp3
          mp3_single_loop (true);
          mp3_stopper = true;
        }
        
        leftMotor.write(LEFT_STRETCHED_POSITION);
        for (int i = 0; i < 30; i++) {
            if (thereIsSomeone()) {
                leftMotor.write(LEFT_REST_POSITION);
                delay(400);
                mp3_stop ();
                return;
            }
        }
        
        leftMotor.write(LEFT_REST_POSITION);
        for (int i = 0; i < 30; i++) {
            if (thereIsSomeone()) {
                delay(400);
                mp3_stop ();
                return;
            }
            
        }
    
        rightMotor.write(RIGHT_STRETCHED_POSITION);
        for (int i = 0; i < 30; i++) {
            if (thereIsSomeone()) {
                rightMotor.write(RIGHT_REST_POSITION);
                delay(400);
                mp3_stop ();
                return;
            }
        }
        
        rightMotor.write(RIGHT_REST_POSITION);
        for (int i = 0; i < 30; i++) {
            if (thereIsSomeone()) {
                delay(400);
                mp3_stop ();
                return;
            }
        }
   }

}

void cin_cin_engagement() 
{
    // Funzione che fa compiere la prima interazione con l'utente
    // Cin Cin chiama verso di se l'utente e se rileva un avvicinamento si presenta per poi fare un inchino
    // Se l'utente Ã¨ ancora lÃ¬ allora la funzione ritorna, altrimenti viene settato il flag somene a FALSE prima di ritornare

    if (thereIsSomeone() && !clientEngaged()) {
        mp3_pause();

        //mp3_play(2); "EHI EHI VIENI QUI!!!
        //se la persona si avvicina

        bowMotorDown();
        bowMotorUp();
        
        engagement = 1;
        //mp3_play(3); "(inchino) MOLTO PIACERE DI CONOSCERTI, IO SONO CIN CIN"
    }


}

void cin_cin_menu() 
{
    // Funzione che fa presentare il ristorante e offrire il menù all'utente
    // Cin Cin presenta il ristorante all'utente per poi invitarlo a dare un'occhiata al menÃ¹ facendo un inchino
    // Se l'utente non prende il menÃ¹ allora Cin Cin si rialza e verifica che l'utente sia ancora lÃ¬, ed eventualmente setta il flag someone a FALSE prima di ritornare
    // Se l'utente Ã¨ ancora lÃ¬ riprova ad offrirgli il menÃ¹, se non viene preso nemmeno questa volta la funzione ritorna
    // Se l'utente prende il menÃ¹ Cin Cin resta inchinato fino a che non viene rimesso a posto, per poi ritornare dopo aver eventualmente settato il flag someone

}

void cin_cin_selfie() 
{
    // Funzione che fa scattare un selfie con l'utente ed invia la foto in cassa tramite Wi-Fi
    // Cin Cin chiede all'utente di scattarsi un selfie con lui e si gira alzando il bambÃ¹, invitandolo a premere il cappello per scattare la foto
    // Se l'utente non preme il cappello allora Cin Cin lo invita nuovamente a schiacciare il cappello non appena Ã¨ pronto
    // Sia che l'utente prema o non prema il cappello, Cin Cin si rimette in posizione normale ed eventualmente setta il flag someone a FALSE prima di ritornare

}

void bowMotorDown()
{
    for (int i = BOW_REST_POSITION; i < BOW_STRETCHED_POSITION; i++) {
        bowMotor.write(i);
    }
    delay(BOW_DOWN_DELAY);
}

void bowMotorUp()
{
    for (int i = BOW_STRETCHED_POSITION; i > BOW_REST_POSITION; i--) {
        bowMotor.write(i);
    }
    delay(BOW_UP_DELAY);
}

void selfie_rotation() 
{
    // Funzione che alza il braccio e fa ruotare Cin Cin per scattare il selfie

}



void updateDistances() 
{
    distanceRight = sonarRight.ping_cm();
    if (distanceRight == 0) {
        distanceRight = MAX_DISTANCE;
    }

    distanceMiddle = sonarMiddle.ping_cm();
    if (distanceMiddle == 0.0) {
        distanceMiddle = MAX_DISTANCE;
    }

    distanceLeft = sonarLeft.ping_cm();
    if (distanceLeft == 0.0) {
        distanceLeft = MAX_DISTANCE;
    }

    debug('R', distanceRight);
    debug('M', distanceMiddle);
    debug('L', distanceLeft);

}

boolean thereIsSomeone() 
{
    updateDistances();
    
    if (distanceRight < STOP_DISTANCE || distanceMiddle < STOP_DISTANCE || distanceLeft < STOP_DISTANCE){
        clientPresence = TRUE;
    } else {
        clientPresence = FALSE;
    }
    return clientPresence;
}

boolean clientEngaged()
{
    return engagement;
}


void turnCameraOn()
{
}
void turnCameraOff()
{
}
void takePicture()
{
}
void switchWifiOn()
{
}
void switchWifiOff()
{
}


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
