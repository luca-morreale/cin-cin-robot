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


// ---- SONAR DISTANCES DEBUGGING ----
#define DEBUG 1


// ---- SONAR PINS ----
#define TRIGPINLEFT 2
#define ECHOPINLEFT 3
#define TRIGPINMIDDLE 4
#define ECHOPINMIDDLE 5
#define TRIGPINRIGHT 6
#define ECHOPINRIGHT 7


// ---- MP3 PLAYER PINS ----
#define RXPIN 12
#define TXPIN 13


// ---- MAXIMUM SONAR DISTANCE (CM) ----
#define MAX_DISTANCE 300


// ---- STOPPING DANCE DISTANCE (CM) ----
#define STOP_DISTANCE 50


// ---- FUNCTION PROTOTYPES ----
void cin_cin_dance(); // Funzione che fa ballare Cin Cin con musica cinese di sottofondo

void cin_cin_engagement(); // Funzione che fa compiere la prima interazione con l'utente

void cin_cin_menu(); // Funzione che fa presentare il ristorante e offrire il menù all'utente

void cin_cin_selfie(); // Funzione che fa scattare un selfie con l'utente ed invia la foto in cassa tramite Wi-Fi

void bow_down(); // Funzione che fa inchinare Cin Cin

void bow_up(); // Funzione che fa rialzare Cin Cin dall'inchino

void selfie_rotation(); // Funzione che alza il braccio e fa ruotare Cin Cin per scattare il selfie

void debugDistance(long distance, char c); // Funzione che permette di stampare a video i valori rilevati dai sonar

void updateDistances(); // Funzione che aggiorna i valori rilevati dai sonar

void is_there_someone(); // Funzione che setta il booleano di presenza utente someone


// ---- SONAR INITIALIZATION ---- 
long distanceLeft, distanceMiddle, distanceRight;
NewPing sonarLeft(TRIGPINLEFT, ECHOPINLEFT, MAX_DISTANCE);
NewPing sonarMiddle(TRIGPINMIDDLE, ECHOPINMIDDLE, MAX_DISTANCE);
NewPing sonarRight(TRIGPINRIGHT, ECHOPINRIGHT, MAX_DISTANCE);


// ---- MOTOR INITIALIZATION ----
Servo leftMotor, rightMotor, bowMotor, rarmMotor;


// ---- MP3 PLAYER INITIALIZATION ----
SoftwareSerial mySerial(RXPIN, TXPIN);


// ---- CONTROL VARIABLES ----
boolean someone = false; // booleano che indica la presenza o meno dell'utente
boolean engagement = false;
boolean mp3_stopper = false; 

void setup() {

  // Inizializzazione dei motori e dei vari componenti
  // Settaggio dei pin di OUTPUT ed INPUT

  leftMotor.attach(LEFT_PIN);
  rightMotor.attach(RIGHT_PIN);
  bowMotor.attach(BOW_PIN);
  rarmMotor.attach(RIGHT_ARM);

  leftMotor.write(LEFT_REST_POSITION);
  rightMotor.write(RIGHT_REST_POSITION);
  bowMotor.write(BOW_REST_POSITION);   
  rarmMotor.write(LEFT_REST_POSITION);

  Serial.begin(9600);
  mySerial.begin(9600);
  mp3_set_serial (mySerial); //set Serial for DFPlayer-mini mp3 module
  mp3_set_volume (20); //max volume is 30

  distanceLeft = 0;
  distanceMiddle = 0;
  distanceRight = 0;
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

   while(true){
    if(!mp3_stopper){
      mp3_play (1); // play 0001.mp3
      mp3_single_loop (true);
      mp3_stopper = true;
    }
    
    leftMotor.write(LEFT_STRETCHED_POSITION);
    for (int i = 0; i < 30; i++)
      updateDistances();
    if (distanceRight < STOP_DISTANCE || distanceMiddle < STOP_DISTANCE || distanceLeft < STOP_DISTANCE){
      leftMotor.write(LEFT_REST_POSITION);
      someone = true;
      delay(400);
      mp3_stop ();
      return;
    }
    
    leftMotor.write(LEFT_REST_POSITION);
    for (int i = 0; i < 30; i++)
      updateDistances();
    if (distanceRight < STOP_DISTANCE || distanceMiddle < STOP_DISTANCE || distanceLeft < STOP_DISTANCE){
      someone = true;
      delay(400);
      mp3_stop ();
      return;
    }

    rightMotor.write(RIGHT_STRETCHED_POSITION);
    for (int i = 0; i < 30; i++)
      updateDistances();
    if (distanceRight < STOP_DISTANCE || distanceMiddle < STOP_DISTANCE || distanceLeft < STOP_DISTANCE){
      rightMotor.write(RIGHT_REST_POSITION);
      someone = true;
      delay(400);
      mp3_stop ();
      return;
    }

    rightMotor.write(RIGHT_REST_POSITION);
    for (int i = 0; i < 30; i++)
      updateDistances();
    if (distanceRight < STOP_DISTANCE || distanceMiddle < STOP_DISTANCE || distanceLeft < STOP_DISTANCE){
      someone = true;
      delay(400);
      mp3_stop ();
      return;
    }
   }
}

void cin_cin_engagement() {

  // Funzione che fa compiere la prima interazione con l'utente
  // Cin Cin chiama verso di se l'utente e se rileva un avvicinamento si presenta per poi fare un inchino
  // Se l'utente Ã¨ ancora lÃ¬ allora la funzione ritorna, altrimenti viene settato il flag somene a FALSE prima di ritornare

  for (int i = BOW_REST_POSITION; i < BOW_STRETCHED_POSITION; i++)
      bowMotor.write(i);
  delay(1000);
  for (int i = BOW_STRETCHED_POSITION; i > BOW_REST_POSITION; i--) 
      bowMotor.write(i);
  delay(1000);
  
  /*if (mp3_stopper == 1 && engagement == 0) {
    mp3_pause ();
    
    //mp3_play(2); "EHI EHI VIENI QUI!!!
    //se la persona si avvicina
    
    for (int i = BOW_REST_POSITION; i < BOW_STRETCHED_POSITION; i++) {
      bowMotor.write(i);
    }
    delay(1000);
    for (int i = BOW_STRETCHED_POSITION; i > BOW_REST_POSITION; i--) {
      bowMotor.write(i);
    }
    delay(1000);
    engagement = 1;
    //mp3_play(3); "(inchino) MOLTO PIACERE DI CONOSCERTI, IO SONO CIN CIN"
  }*/


}

void cin_cin_menu() {

  // Funzione che fa presentare il ristorante e offrire il menù all'utente
  // Cin Cin presenta il ristorante all'utente per poi invitarlo a dare un'occhiata al menÃ¹ facendo un inchino
  // Se l'utente non prende il menÃ¹ allora Cin Cin si rialza e verifica che l'utente sia ancora lÃ¬, ed eventualmente setta il flag someone a FALSE prima di ritornare
  // Se l'utente Ã¨ ancora lÃ¬ riprova ad offrirgli il menÃ¹, se non viene preso nemmeno questa volta la funzione ritorna
  // Se l'utente prende il menÃ¹ Cin Cin resta inchinato fino a che non viene rimesso a posto, per poi ritornare dopo aver eventualmente settato il flag someone

}

void cin_cin_selfie() {

  // Funzione che fa scattare un selfie con l'utente ed invia la foto in cassa tramite Wi-Fi
  // Cin Cin chiede all'utente di scattarsi un selfie con lui e si gira alzando il bambÃ¹, invitandolo a premere il cappello per scattare la foto
  // Se l'utente non preme il cappello allora Cin Cin lo invita nuovamente a schiacciare il cappello non appena Ã¨ pronto
  // Sia che l'utente prema o non prema il cappello, Cin Cin si rimette in posizione normale ed eventualmente setta il flag someone a FALSE prima di ritornare

}

// -------------- HELPER FUNCTIONS --------------

void bow_down() {

  // Funzione che fa inchinare Cin Cin

}

void bow_up() {

  // Funzione che fa rialzare Cin Cin dall'inchino

}

void selfie_rotation() {

  // Funzione che alza il braccio e fa ruotare Cin Cin per scattare il selfie

}

void debugDistance(long distance, char c)
{
  if (DEBUG) {
    Serial.print(c);
    Serial.print(": ");
    Serial.println(distance);
    Serial.println("");
  }
}

void updateDistances() {

  distanceRight = sonarRight.ping_cm();
  if (distanceRight == 0)
    distanceRight = MAX_DISTANCE;

  distanceMiddle = sonarMiddle.ping_cm();
  if (distanceMiddle == 0.0)
    distanceMiddle = MAX_DISTANCE;

  distanceLeft = sonarLeft.ping_cm();
  if (distanceLeft == 0.0)
    distanceLeft = MAX_DISTANCE;

  debugDistance(distanceRight, 'R');
  debugDistance(distanceMiddle, 'M');
  debugDistance(distanceLeft, 'L');

}

void is_there_someone() {

  // Funzione che setta il booleano di presenza utente someone

}
