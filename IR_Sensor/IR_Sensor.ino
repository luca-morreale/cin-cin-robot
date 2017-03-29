#define sensor A0 // Sharp IR (10-80 cm)

void setup() {
  Serial.begin(9600); // start the serial port
}

void loop() {
  
  // 5v
  float volts = analogRead(sensor);  // value from sensor * (5/1024)
  int distance = (6762/(volts-9))-4; // worked out from datasheet graph
  delay(1000); // slow down serial port 
  
    Serial.println(distance);   // print the distance
}
