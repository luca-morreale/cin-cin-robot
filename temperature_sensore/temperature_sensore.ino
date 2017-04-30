void setup()
{
    //Init Seriale
    Serial.begin(9600);
    pinMode(A1, INPUT);
}

void loop()
{
    delay(10);
    int val_ADC = analogRead(A1);
    //invio il dato acquisito al pc
    Serial.println(val_ADC);
}
