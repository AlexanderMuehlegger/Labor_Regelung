#define ausgang A0
#define eingang A1

void setup() {
  pinMode(ausgang, INPUT);
  pinMode(eingang, INPUT);
  Serial.begin(9600);
}

long old = 0;

void loop() {
  if(millis() - old >= 200){
    int _ein = analogRead(eingang);
    int _aus = analogRead(ausgang);
    
    Serial.print(_ein);
    Serial.print("\t");
    Serial.println(_aus);
    old = millis();
  }
  

}

const float k = 0.37;
const float d = 319.55;
const float _vorWiderstand = 8050.0;

void detTemp(int _aus){
  int _ein = k*_aus + d;
  
  
}
