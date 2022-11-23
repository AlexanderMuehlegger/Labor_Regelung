#define lampe 5

void setup() {
  pinMode(lampe, OUTPUT);
  Serial.begin(9600);

}

float old = 0;
int value = 0;

void loop() {
  if(millis()-old >= 500){
    Serial.println(value);
    analogWrite(lampe, value);

    value += 50;
    if(value == 250)
      value = 0;
     
    
    old = millis();
  }
  /*
  if(Serial.available() > 0){
    String mode = Serial.readString();

    int wert = mode.toInt();
    Serial.println(wert);
    analogWrite(lampe, wert);
  }*/
}
