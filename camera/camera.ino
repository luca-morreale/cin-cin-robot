
/*
 * Code to turn on and off the camera. (readable version)
 *
 * Circuit:
 * Connect the GND of the camera with resistence R1.
 * Connect resistence R1 with GND of Arduino.
 * Connect the pin of the camera with pin 10 of Arduino.
 */

#define CAMERA_PIN 10

#define ON 1
#define OFF 0

#define TURN_OFF_DEALY 2000
#define TURN_ON_DELAY 500

int camState = 0;

void setup() {
    Serial.begin(9600);
    pinMode(CAMERA_PIN, OUTPUT);
}


void loop() {
    
    Serial.println("turning on");
    turnOn();
    Serial.println("turn on");
    delay(10000);
    
    Serial.println("turning off");
    turnOff();
    Serial.println("turn off");
    delay(10000);
    
}

void turnOn()
{
    if (camState == OFF) {
        digitalWrite(CAMERA_PIN, LOW);
        delay(TURN_ON_DELAY);
        digitalWrite(CAMERA_PIN, HIGH);
        
        camState = ON;
    }
}

void turnOff()
{
    if (camState == ON) {
        digitalWrite(CAMERA_PIN, LOW);
        delay(TURN_OFF_DEALY);
        digitalWrite(CAMERA_PIN, HIGH);
        
        camState = OFF;
    }
}

