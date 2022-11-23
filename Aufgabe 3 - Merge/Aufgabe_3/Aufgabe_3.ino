#define ausgang A0
#define lampe 5

long old = 0;
long _new = 0;

//Konstanten für die Reggresionsfunktion
const float k = 0.37;
const float d = 319.55;
const float _vorWiderstand = 8050.0;

const float gesamtSpannung = 1024.0;

float heizleistung = 0;
bool heizSet = false;

void setup() {
  pinMode(ausgang, INPUT);
  pinMode(lampe, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  _new = millis();
  if(millis() == 30000 && !heizSet){
    changeheizleistung();
    heizSet = true;
  }
  
  if(_new - old >= 5000){
    float temp = messen();
    Serial.println((String)(_new/1000.0) + "s\t" + (String)heizleistung + "\t" + (String)temp);
    old = _new;
  }
  
  
}


float messen(){
    int _aus = analogRead(ausgang);
    return detTemp((float)_aus);

}

void changeheizleistung(){
  heizleistung = 50;
  analogWrite(lampe, heizleistung);
}

//Hauptfunktion zum errechnen der Temperatur anhand der Ausgangsspannung des NTC's
float detTemp(float _aus){
  float _ein = k*_aus + d; //Durch die Reggresionsfunktion die Eingangsspannung berechnen

  float Rntc = ((gesamtSpannung-_ein)*_vorWiderstand)/_ein; //Wiederstand des NTC's berechnen

  return calcTempFromRes(abs(Rntc))-273.15;
}

//Durch den Widerstand des NTC's wird die Temperatur berechnet 
float calcTempFromRes(float _Rntc){
  if (_Rntc < 0) //Widerstand muss größer wie 0 sein
    return;
    
  float temp = 3950/(log(_Rntc)+ 4.03802); //Durch die Umkehrfunktion der Funktion Rntc(T) (vgl. Skript Regelungstechnik.pdf - Formel 1) 
  return temp;
}
