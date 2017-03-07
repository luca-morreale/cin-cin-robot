Libreria modificata da Daniele Denaro per adattarla all'IDE 1.0 di ARDUINO e 
soprattutto per utilizzarla anche su TiDiGino (o comunque su ARDUINO MEGA).

Per utilizzarla su TiDiGino bisogna scambiare i commenti nel file "spi.h".

Esempio:

Libreria utilizzabile su ARDUINO:

#define ARDUINO1        //UNO
//#define TIDIGINO         //or ATMega2560

Libreria utilizzabile su TiDiGino:

//#define ARDUINO1        //UNO
#define TIDIGINO         //or ATMega2560 