// IMPORTANTE: PER IL CABLAGGIO, TX VA CON RX E VICEVERSA

#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

void setup () {
 Serial.begin (9600);
 mp3_set_serial (Serial); //set Serial for DFPlayer-mini mp3 module 
 mp3_set_volume (30); //max volume is 30 (not really sure)
}
 
void loop () {        

 mp3_play (1); //play 0001.mp3
 delay (30000); //30 sec, time delay to allow 0001.mp3 to finish playing

 mp3_play (1); //play 0001.mp3
 delay(3000);
// mp3_pause (); //pause the mp3

}
