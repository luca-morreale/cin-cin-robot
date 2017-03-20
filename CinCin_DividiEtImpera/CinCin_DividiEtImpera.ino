
#include <Servo.h>

#define LEFT_PIN 9
#define RIGHT_PIN 10
#define BOW_PIN 11
#define RIGHT_ARM 12

#define LEFT_STRETCHED_POSITION 30
#define LEFT_REST_POSITION 180

#define RIGHT_STRETCHED_POSITION 30
#define RIGHT_REST_POSITION 180

#define BOW_STRETCHED_POSITION 160
#define BOW_REST_POSITION 90

#define RARM_HIGH_POSITION 0
#define RARM_LOW_POSITION 90

#define tempo 7

#define SonarPinRight 4
#define SonarPinLeft 5
#define SonarPinMiddle 6

Servo leftMotor, rightMotor, bowMotor, rarmMotor;

long distanceLeft,distanceMiddle,distanceRight; // variabili contenenti le distanze rilevate dai 3 sonar 
boolean someone = false; // booleano che indica la presenza o meno dell'utente
int stop = 0;

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
    distanceLeft = 0;
    distanceMiddle = 0;
    distanceRight = 0;

}

void loop() {

  cin_cin_dance(); 
  cin_cin_engagement();
  if(someone)
    cin_cin_menu();
  if(someone)
    cin_cin_selfie();  
}

void cin_cin_dance(){

  // Funzione che fa ballare Cin Cin con musica cinese di sottofondo
  // Mentre balla rileva se passa qualcuno entro 2 metri c.a.
  // Quando rileva qualcuno si fermano i motori, la musica e la funzione ritorna dopo aver settato il flag someone a TRUE 

  get_Distance();
  
  /*if(!stop){
    for(int i=LEFT_REST_POSITION;i>LEFT_STRETCHED_POSITION;i--){
      leftMotor.write(i);
      delay(tempo);
    }
    get_Distance();
    if(distanceLeft != 0 || distanceMiddle != 0 || distanceRight != 0)
      stop = 1;
 
    for(int i=LEFT_STRETCHED_POSITION;i<LEFT_REST_POSITION;i++){
      leftMotor.write(i);
      delay(tempo);
    }
    get_Distance();
    if(distanceLeft != 0 || distanceMiddle != 0 || distanceRight != 0)
      stop = 1;
  }
   
   // delay(1000);

  if(!stop){
    for(int i=RIGHT_REST_POSITION;i>RIGHT_STRETCHED_POSITION;i--){
      rightMotor.write(i);
      rarmMotor.write(i/2.5);
      delay(tempo);
    }
    get_Distance();
    if(distanceLeft != 0 || distanceMiddle != 0 || distanceRight != 0)
      stop = 1;
    
    for(int i=RIGHT_STRETCHED_POSITION;i<RIGHT_REST_POSITION;i++){
      rightMotor.write(i);
      rarmMotor.write(i/2.5);
      delay(tempo);
    }
    get_Distance();
    if(distanceLeft != 0 || distanceMiddle != 0 || distanceRight != 0)
      stop = 1;
  }*/
}

void cin_cin_engagement(){

  // Funzione che fa compiere la prima interazione con l'utente
  // Cin Cin chiama verso di se l'utente e se rileva un avvicinamento si presenta per poi fare un inchino
  // Se l'utente è ancora lì allora la funzione ritorna, altrimenti viene settato il flag somene a FALSE prima di ritornare
  
}

void cin_cin_menu(){

  // Funzione che fa presentare il ristorante e offrire il menù all'utente
  // Cin Cin presenta il ristorante all'utente per poi invitarlo a dare un'occhiata al menù facendo un inchino
  // Se l'utente non prende il menù allora Cin Cin si rialza e verifica che l'utente sia ancora lì, ed eventualmente setta il flag someone a FALSE prima di ritornare
  // Se l'utente è ancora lì riprova ad offrirgli il menù, se non viene preso nemmeno questa volta la funzione ritorna
  // Se l'utente prende il menù Cin Cin resta inchinato fino a che non viene rimesso a posto, per poi ritornare dopo aver eventualmente settato il flag someone
  
}

void cin_cin_selfie(){

  // Funzione che fa scattare un selfie con l'utente ed invia la foto in cassa tramite Wi-Fi
  // Cin Cin chiede all'utente di scattarsi un selfie con lui e si gira alzando il bambù, invitandolo a premere il cappello per scattare la foto
  // Se l'utente non preme il cappello allora Cin Cin lo invita nuovamente a schiacciare il cappello non appena è pronto
  // Sia che l'utente prema o non prema il cappello, Cin Cin si rimette in posizione normale ed eventualmente setta il flag someone a FALSE prima di ritornare
  
}

// -------------- HELPER FUNCTIONS --------------

void bow_down(){

  // Funzione che fa inchinare Cin Cin
  
}

void bow_up(){

  // Funzione che fa rialzare Cin Cin dall'inchino
  
}

void selfie_rotation(){

 // Funzione che alza il braccio e fa ruotare Cin Cin per scattare il selfie 
  
}

void get_Distance(){

  // Funzione che rileva le distanze percepite dai sonar e le colloca nelle apposite variabili globali
  
  float pulseTime;

  // Right Sonar
  pinMode(SonarPinRight, OUTPUT);
  digitalWrite(SonarPinRight, LOW);      // viene posto a LOW pin
  delayMicroseconds(2);              // per 2 microsecondi
  digitalWrite(SonarPinRight, HIGH);     // invia un impulso di trigger
  delayMicroseconds(10);             // di 10 microsecondi
  digitalWrite(SonarPinRight, LOW);      // pone il pin al LOW in attesa che l'impulso torni indietro

  pinMode(SonarPinRight, INPUT);
  pulseTime = pulseIn(SonarPinRight, HIGH); // legge l'eco dell'impulso emesso in microsecondi
  distanceRight = pulseTime / 58;            // divide la durata per 58 per ottenere la distanza in cm
  if(distanceRight > 100)
    distanceRight = 0;

  // Middle Sonar
  pinMode(SonarPinMiddle, OUTPUT);
  digitalWrite(SonarPinMiddle, LOW);      // viene posto a LOW pin
  delayMicroseconds(2);              // per 2 microsecondi
  digitalWrite(SonarPinMiddle, HIGH);     // invia un impulso di trigger
  delayMicroseconds(10);             // di 10 microsecondi
  digitalWrite(SonarPinMiddle, LOW);      // pone il pin al LOW in attesa che l'impulso torni indietro

  pinMode(SonarPinMiddle, INPUT);
  pulseTime = pulseIn(SonarPinMiddle, HIGH); // legge l'eco dell'impulso emesso in microsecondi
  distanceMiddle = pulseTime / 58;            // divide la durata per 58 per ottenere la distanza in cm
  if(distanceMiddle > 100)
    distanceMiddle = 0;

  // Left Sonar
  pinMode(SonarPinLeft, OUTPUT);
  digitalWrite(SonarPinLeft, LOW);      // viene posto a LOW pin
  delayMicroseconds(2);              // per 2 microsecondi
  digitalWrite(SonarPinLeft, HIGH);     // invia un impulso di trigger
  delayMicroseconds(10);             // di 10 microsecondi
  digitalWrite(SonarPinLeft, LOW);      // pone il pin al LOW in attesa che l'impulso torni indietro

  pinMode(SonarPinLeft, INPUT);
  pulseTime = pulseIn(SonarPinLeft, HIGH); // legge l'eco dell'impulso emesso in microsecondi
  distanceLeft = pulseTime / 58;            // divide la durata per 58 per ottenere la distanza in cm
  if(distanceLeft > 100)
    distanceLeft = 0;
  
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

void is_there_someone(){

  // Funzione che setta il booleano di presenza utente someone
  
}



