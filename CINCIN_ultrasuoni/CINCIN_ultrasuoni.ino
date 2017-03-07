
// CINCIN ultrasuoni (readable version)
// turn on led when distance below 15cm
// blink when between 15cm and 60 cm

#define DEBUG 1

#define BOUD_RATE 9600
#define SIGNAL_PIN 8
#define LED_PIN 9
#define NUM_READINGS 3

#define LOW_DISTANCE 15
#define FAR_DISTANCE 60

#define DELAY_LED_BLINKING 100

int currentIndex;
float distances[NUM_READINGS];
float totalDistance;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT) ;

  currentIndex = 0;
  clearTotal();
  clearDistances();
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
    digitalWrite(LED_PIN, HIGH) ;
  } else if (avgDistance > LOW_DISTANCE && avgDistance < FAR_DISTANCE) {
    digitalWrite(LED_PIN,HIGH);
    delay(DELAY_LED_BLINKING);
    digitalWrite(LED_PIN,LOW);
    delay(DELAY_LED_BLINKING);
  } else {  // if (avgDistance > FAR_DISTANCE) 
    digitalWrite(LED_PIN,LOW);
 }
 debugDistance(avgDistance);
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


