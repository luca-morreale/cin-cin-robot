
/*
 * Code to turn on and off the camera. (readable version)
 *
 * Circuit for button power:
 * Connect the GND of the camera with resistence R1(220).
 * Connect resistence R1 with GND of Arduino.
 * Connect the pin of the camera with pin 10 of Arduino.
 *
 * Circuit for picture button:
 * Connect pin 11 of arduino to breadboard
 * Connect resistor of ... from line of pin 11 to another line in breadboard
 * Connect wire from the camera to the other side of resistor.
 *
 */

#define CAMERA_PIN 21
#define CAMERA_SHOT_PIN 20

#define ON 1
#define OFF 0

#define TURN_ON_DELAY 200
#define TURN_OFF_DELAY 4000
#define SHOOT_DELAY 300        // if increased will take a video!
#define SWITCH_STAGE_DELAY 500
#define WIFI_ON_DELAY 4000
#define WIFI_OFF_DELAY 4000

int camState = OFF;
int wifiState = OFF;

void setup() {
    Serial.begin(9600);
    pinMode(CAMERA_PIN, OUTPUT);
    pinMode(CAMERA_SHOT_PIN, OUTPUT);
    
    initPinCamera();
}

void loop() {

    //"fai un selfie con me?"
    Serial.println("turning on");
    turnOnCamera();
    Serial.println("turn on");
    delay(5000);
    
    //la persona tocca il sensore touch
    Serial.println("taking pic");
    takePicture();
    Serial.println("taken pic");
    delay(5000);
    switchOnWiFi();
    Serial.println("Wifi active");
    delay(120000);
    switchOffWiFi();
    Serial.println("Wifi deactive");
    
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
        delay(5000);    // wait it turns on
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
    }
}

void switchToPictureStage()
{
    
    for (int i = 0; i < 2; i++) {
        Serial.println("changing state");
        digitalWrite(CAMERA_PIN, LOW);
        delay(SWITCH_STAGE_DELAY);
        digitalWrite(CAMERA_PIN, HIGH);
        delay(SWITCH_STAGE_DELAY);
    }
}

void switchOnWiFi()
{
    if (camState == ON && wifiState == OFF) {
        Serial.println("inside wifi");
        digitalWrite(CAMERA_SHOT_PIN, HIGH);
        delay(WIFI_ON_DELAY);
        digitalWrite(CAMERA_SHOT_PIN, LOW);
        
        wifiState = ON;
    }
}

void switchOffWiFi()
{
    if (camState == ON && wifiState == ON) {
        Serial.println("outside wifi");
        digitalWrite(CAMERA_SHOT_PIN, HIGH);
        delay(WIFI_OFF_DELAY);
        digitalWrite(CAMERA_SHOT_PIN, LOW);
        
        wifiState = OFF;
    }
}

