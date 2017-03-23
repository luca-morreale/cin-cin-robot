
/*
 * Code to turn on and off the camera. (readable version)
 *
 * Circuit for button power:
 * Connect the GND of the camera with resistence R1.
 * Connect resistence R1 with GND of Arduino.
 * Connect the pin of the camera with pin 10 of Arduino.
 *
 * Circuit for picture button:
 * Connect pin 11 of arduino to breadboard
 * Connect resistor of ... from line of pin 11 to another line in breadboard
 * Connect wire from the camera to the other side of resistor.
 *
 */

#define CAMERA_PIN 10
#define CAMERA_SHOT_PIN 11

#define ON 1
#define OFF 0

#define TURN_OFF_DEALY 2000
#define TURN_ON_DELAY 200
#define SHOOT_DELAY 200
#define SWITCH_STAGE_DELAY 200
#define WIFI_ON_DELAY 3000
#define WIFI_OFF_DELAY 3000

int camState = 0;
int wifiState = 0;

void setup() {
    Serial.begin(9600);
    pinMode(CAMERA_PIN, OUTPUT);
    pinMode(CAMERA_SHOT_PIN, OUTPUT);
    
    initPinCamera();
}

void loop() {
    
    Serial.println("turning on");
    turnOnCamera();
    Serial.println("turn on");
    delay(10000);
    
    takePicture();
    
    Serial.println("turning off");
    turnOffCamera();
    Serial.println("turn off");
    delay(10000);
    
}

void initPinCamera()
{
    digitalWrite(CAMERA_PIN, HIGH);
    digitalWrite(CAMERA_SHOT_PIN, LOW);
}

void turnOnCamera()
{
    if (camState == OFF) {
        digitalWrite(CAMERA_PIN, LOW);
        delay(TURN_ON_DELAY);
        digitalWrite(CAMERA_PIN, HIGH);
        
        camState = ON;
    }
}

void turnOffCamera()
{
    if (camState == ON) {
        digitalWrite(CAMERA_PIN, LOW);
        delay(TURN_OFF_DEALY);
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
    }
}

void switchToPictureStage()
{
    
    for (int i = 0; i < 2; i++) {
        digitalWrite(CAMERA_SHOT_PIN, LOW);
        delay(SWITCH_STAGE_DELAY);
        digitalWrite(CAMERA_SHOT_PIN, HIGH);
        delay(SWITCH_STAGE_DELAY);
    }
}

void switchOnWiFi()
{
    if (camState == ON && wifiState == OFF) {
        digitalWrite(CAMERA_SHOT_PIN, LOW);
        delay(WIFI_ON_DELAY);
        digitalWrite(CAMERA_SHOT_PIN, HIGH);
        
        wifiState = ON;
    }
}

void switchOffWiFi()
{
    if (camState == ON && wifiState == ON) {
        digitalWrite(CAMERA_SHOT_PIN, LOW);
        delay(WIFI_OFF_DELAY);
        digitalWrite(CAMERA_SHOT_PIN, HIGH);
        
        wifiState = OFF;
    }
}

