
// CINCIN ultrasuoni (readable version)
// turn on led when distance below 15cm
// blink when between 15cm and 60 cm

#define DEBUG 1

#define BOUD_RATE 9600
#define SIGNAL_PIN_RIGHT 4
#define SIGNAL_PIN_LEFT 5
#define SIGNAL_PIN_MIDDLE 6
#define NUM_READINGS 3

#define LOW_DISTANCE 15
#define FAR_DISTANCE 60

#define DELAY_LED_BLINKING 100

int currentIndex;
float distances_right[NUM_READINGS];
float distances_left[NUM_READINGS];
float distances_middle[NUM_READINGS];
float totalDistance_right;
float totalDistance_left;
float totalDistance_middle;

void setup() {
  Serial.begin(9600);

  currentIndex = 0;
  clearTotal(&totalDistance_right);
  clearTotal(&totalDistance_left);
  clearTotal(&totalDistance_middle);
  
  clearDistances(distances_right);
  clearDistances(distances_left);
  clearDistances(distances_middle);
}

void loop() {
  float distance_right = getDistance(SIGNAL_PIN_RIGHT);
  float distance_left = getDistance(SIGNAL_PIN_LEFT);
  float distance_middle = getDistance(SIGNAL_PIN_MIDDLE);

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

  if ((isTooFar(distances_right)) || (isTooFar(distances_left)) || (isTooFar(distances_middle))) {
    clearTotal(&totalDistance_right);
    clearDistances(distances_right);
    
    clearTotal(&totalDistance_left);
    clearDistances(distances_left);
    
    clearTotal(&totalDistance_middle);
    clearDistances(distances_middle);
    
  } else {
    performBehavior(averageDistance(totalDistance_right));
    performBehavior(averageDistance(totalDistance_left));
    performBehavior(averageDistance(totalDistance_middle));
  }
  
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

void performBehavior(float avgDistance)
{
//  if (avgDistance < LOW_DISTANCE) {
//    digitalWrite(LED_PIN, HIGH) ;
//  } else if (avgDistance > LOW_DISTANCE && avgDistance < FAR_DISTANCE) {
//    digitalWrite(LED_PIN,HIGH);
//    delay(DELAY_LED_BLINKING);
//    digitalWrite(LED_PIN,LOW);
//    delay(DELAY_LED_BLINKING);
//  } else {  // if (avgDistance > FAR_DISTANCE) 
//    digitalWrite(LED_PIN,LOW);
// }
 debugDistance(avgDistance);
}

void debugDistance(float avgDistance)
{
  if (DEBUG) {
    Serial.println(avgDistance);
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


