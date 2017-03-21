// IMPORTANTISSIMO: I SONAR VANNO ALIMENTATI A PARTE (5 V)


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

#define DEBUG 1

#define BOUD_RATE 9600
#define SIGNAL_PIN_RIGHT 4
#define SIGNAL_PIN_LEFT 5
#define SIGNAL_PIN_MIDDLE 6
#define NUM_READINGS 3

int currentIndex;
float distances_right[NUM_READINGS];
float distances_left[NUM_READINGS];
float distances_middle[NUM_READINGS];
float totalDistance_right;
float totalDistance_left;
float totalDistance_middle;
float distance_right;
float distance_left;
float distance_middle;

Servo leftMotor, rightMotor, bowMotor, rarmMotor;

boolean someone = false; // booleano che indica la presenza o meno dell'utente
int stopper = 0;

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

    currentIndex = 0;
    clearTotal(&totalDistance_right);
    clearTotal(&totalDistance_left);
    clearTotal(&totalDistance_middle);
  
    clearDistances(distances_right);
    clearDistances(distances_left);
    clearDistances(distances_middle);

    for(int i=0;i<NUM_READINGS;i++)
      updateDistances();
    stopper = 0;
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
  
  if(!stopper){
    //for(int i=LEFT_REST_POSITION;i>LEFT_STRETCHED_POSITION;i--){
      leftMotor.write(LEFT_STRETCHED_POSITION);
      for(int i=0;i<15;i++)
        updateDistances();
    //}
 
    //for(int i=LEFT_STRETCHED_POSITION;i<LEFT_REST_POSITION;i++){
      leftMotor.write(LEFT_REST_POSITION);
      for(int i=0;i<15;i++)
        updateDistances();
    //}
  }

  if(!stopper){
    //for(int i=RIGHT_REST_POSITION;i>RIGHT_STRETCHED_POSITION;i--){
      rightMotor.write(RIGHT_STRETCHED_POSITION);
      for(int i=0;i<15;i++)
        updateDistances();
      //rarmMotor.write(i/2.5);
      
    //}
    
    //for(int i=RIGHT_STRETCHED_POSITION;i<RIGHT_REST_POSITION;i++){
      rightMotor.write(RIGHT_REST_POSITION);
      for(int i=0;i<15;i++)
        updateDistances();
      //rarmMotor.write(i/2.5);
       
    //}
  }
}

void cin_cin_engagement(){

  // Funzione che fa compiere la prima interazione con l'utente
  // Cin Cin chiama verso di se l'utente e se rileva un avvicinamento si presenta per poi fare un inchino
  // Se l'utente Ã¨ ancora lÃ¬ allora la funzione ritorna, altrimenti viene settato il flag somene a FALSE prima di ritornare
  
}

void cin_cin_menu(){

  // Funzione che fa presentare il ristorante e offrire il menÃ¹ all'utente
  // Cin Cin presenta il ristorante all'utente per poi invitarlo a dare un'occhiata al menÃ¹ facendo un inchino
  // Se l'utente non prende il menÃ¹ allora Cin Cin si rialza e verifica che l'utente sia ancora lÃ¬, ed eventualmente setta il flag someone a FALSE prima di ritornare
  // Se l'utente Ã¨ ancora lÃ¬ riprova ad offrirgli il menÃ¹, se non viene preso nemmeno questa volta la funzione ritorna
  // Se l'utente prende il menÃ¹ Cin Cin resta inchinato fino a che non viene rimesso a posto, per poi ritornare dopo aver eventualmente settato il flag someone
  
}

void cin_cin_selfie(){

  // Funzione che fa scattare un selfie con l'utente ed invia la foto in cassa tramite Wi-Fi
  // Cin Cin chiede all'utente di scattarsi un selfie con lui e si gira alzando il bambÃ¹, invitandolo a premere il cappello per scattare la foto
  // Se l'utente non preme il cappello allora Cin Cin lo invita nuovamente a schiacciare il cappello non appena Ã¨ pronto
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

float averageDistance(float totalDistance)
{
  return totalDistance / NUM_READINGS;
}

void removeFirstDistance(float *totalDistance, float *distances)
{
  *totalDistance -= distances[0];
}

void shiftDistances(float *distances)
{
  for (int i=0; i < NUM_READINGS-1; i++) {
    distances[i] = distances[i + 1];
  }
  distances[NUM_READINGS - 1] = 0;
}

void appendDistance(float distance,float *distances)
{
  distances[currentIndex++] = distance;
  if (currentIndex >= NUM_READINGS) {
    currentIndex = NUM_READINGS - 1;
  }
}

int isTooFar(float *distances)
{
  return getDistanceFromEnd(0,distances) == 0 && getDistanceFromEnd(1,distances) == 0;
}

float getDistanceFromEnd(int position,float *distances)
{
  return (currentIndex-position > 0)? distances[currentIndex-position] : 0;
}

void debugDistance(float avgDistance)
{
  if (DEBUG) {
    Serial.println(avgDistance);
    Serial.println("");
  }
}

float getDistance(int pin)
{
  // durata dell'impulso
  float pulseTime;
  float distanza;

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);      // viene posto a LOW pin
  delayMicroseconds(2);              // per 2 microsecondi
  digitalWrite(pin, HIGH);     // invia un impulso di trigger
  delayMicroseconds(10);             // di 10 microsecondi
  digitalWrite(pin, LOW);      // pone il pin al LOW in attesa che l'impulso torni indietro

  pinMode(pin, INPUT);
  pulseTime = pulseIn(pin, HIGH); // legge l'eco dell'impulso emesso in microsecondi
  return pulseTime / 58;            // divide la durata per 58 per ottenere la distanza in cm
}

void clearTotal(float *totalDistance)
{
 *totalDistance = 0;
}

void clearDistances(float *distances)
{
  for (int i=0; i<NUM_READINGS; i++) {
    distances[i] = 0;
  }
}

void updateDistances(){

  distance_right = getDistance(SIGNAL_PIN_RIGHT);
  distance_left = getDistance(SIGNAL_PIN_LEFT);
  distance_middle = getDistance(SIGNAL_PIN_MIDDLE);

  removeFirstDistance(&totalDistance_right,distances_right);
  removeFirstDistance(&totalDistance_left,distances_left);
  removeFirstDistance(&totalDistance_middle,distances_middle);
  
  shiftDistances(distances_right);
  shiftDistances(distances_left);
  shiftDistances(distances_middle);

  totalDistance_right += distance_right;
  appendDistance(distance_right,distances_right);
  
  totalDistance_left += distance_left;
  appendDistance(distance_left,distances_left);
  
  totalDistance_middle += distance_middle;
  appendDistance(distance_middle,distances_middle);

  debugDistance(averageDistance(totalDistance_right));
  debugDistance(averageDistance(totalDistance_left));
  debugDistance(averageDistance(totalDistance_middle));
  
  if(averageDistance(totalDistance_right) < 50 || averageDistance(totalDistance_middle) < 50 || averageDistance(totalDistance_left) < 50)
        stopper = 1;
  
}

void is_there_someone(){

  // Funzione che setta il booleano di presenza utente someone
  
}




