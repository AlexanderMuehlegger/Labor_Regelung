#include <stdarg.h>
#define ausgang A0
#define eingang A1

long old = 0;

//Konstanten für die Reggresionsfunktion
const float k = 0.37;
const float d = 319.55;
const float _vorWiderstand = 8050.0;

const float gesamtSpannung = 1024.0;


void setup() {
  pinMode(ausgang, INPUT);
  pinMode(eingang, INPUT);
  Serial.begin(9600);
}



void loop() {
  if(millis() - old >= 1000){
    messen();
    old = millis();
  }
}

float messen(){
  
    int _ein = analogRead(eingang);
    int _aus = analogRead(ausgang);
    
    //Serial.print(_ein);
    //Serial.print("\t");
    //Serial.println(_aus);

    detTemp((float)_aus);

}


//Hauptfunktion zum errechnen der Temperatur anhand der Ausgangsspannung des NTC's
float detTemp(float _aus){
  float _ein = k*_aus + d; //Durch die Reggresionsfunktion die Eingangsspannung berechnen

  float Rntc = ((gesamtSpannung-_ein)*_vorWiderstand)/_ein; //Wiederstand des NTC's berechnen
  
  Serial.print("Rntc: "); //Ausgabe des errechneten Wiederstands und der Temperatur
  Serial.println(Rntc);
  Serial.print("Temp: ");
  Serial.print(calcTempFromRes(abs(Rntc))-273.15);
  Serial.println("°C");
  return calcTempFromRes(abs(Rntc))-273.15;
}

//Durch den Widerstand des NTC's wird die Temperatur berechnet 
float calcTempFromRes(float _Rntc){
  if (_Rntc < 0) //Widerstand muss größer wie 0 sein
    return;
    
  float temp = 3950/(log(_Rntc)+ 4.03802); //Durch die Umkehrfunktion der Funktion Rntc(T) (vgl. Skript Regelungstechnik.pdf - Formel 1) 
  return temp;
}
