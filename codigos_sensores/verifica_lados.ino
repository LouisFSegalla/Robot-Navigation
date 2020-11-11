#include <Ultrasonic.h>

#define TRIGGER_PIN  48
#define ECHO_PIN     41

#define TRIGGER_PIN2  36
#define ECHO_PIN2     37

#define TRIGGER_PIN3  26
#define ECHO_PIN3     24

int caminhos[3] = {0, 0, 0};
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Ultrasonic ultrasonic2(TRIGGER_PIN2, ECHO_PIN2);
Ultrasonic ultrasonic3(TRIGGER_PIN3, ECHO_PIN3);

const int pinoLedVerde2 =10 ;
const int pinoLedAmarelo = 9;
const int pinoLedAzul =8 ;

void verifica_lados(){
    float cmMsec, inMsec, cmMsec2, inMsec2, cmMsec3, inMsec3;
  long microsec = ultrasonic.timing();
  long microsec2 = ultrasonic2.timing();
  long microsec3 = ultrasonic3.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  cmMsec2 = ultrasonic2.convert(microsec2, Ultrasonic::CM);
  cmMsec3 = ultrasonic3.convert(microsec3, Ultrasonic::CM);
 //verifica_lados(cmMsec, cmMsec2, cmMsec3);
    caminhos[0] = 0;
  caminhos[1] = 0;
  caminhos[2] = 0;
  if(cmMsec > 10){
      caminhos[0] = 1;
  }
  if(cmMsec2 > 10){
      caminhos[1] = 2;
  }
  if(cmMsec3 > 10){
      caminhos[2] = 3;
  }
  //Serial.print("MS: ");
 // Serial.print(microsec);
  Serial.print(" CM: ");
  Serial.print(cmMsec);
  Serial.print("pode ou não: ");
  Serial.print(caminhos[0]);

  //Serial.print(" | MS2:  ");
  //Serial.print(microsec2);
   Serial.print(", CM: ");
  Serial.print(cmMsec2);
  Serial.print("pode ou não: ");
  Serial.print(caminhos[1]);


 // Serial.print("| MS3: ");
  //Serial.print(microsec3);
   Serial.print(", CM: ");
  Serial.print(cmMsec3);
  Serial.print("pode ou não: ");
  Serial.println(caminhos[2]);

  if(caminhos[0] != 0){
      digitalWrite(pinoLedAzul, LOW);
     
  }
  else{
    digitalWrite(pinoLedAzul, HIGH);
  }
  if(caminhos[1] != 0){
      digitalWrite(pinoLedAmarelo, LOW);
     
  }
  else{
    digitalWrite(pinoLedAmarelo, HIGH);
  }
   if(caminhos[2] != 0){
      digitalWrite(pinoLedVerde2, LOW);
     
  }
  else{
    digitalWrite(pinoLedVerde2, HIGH);
  }
  
  delay(1000);

}

void setup()
  {
  Serial.begin(9600);
  pinMode(pinoLedVerde2, OUTPUT);
  pinMode(pinoLedAmarelo, OUTPUT);
  pinMode(pinoLedAzul, OUTPUT);
   pinMode(pinoLedAzul, LOW);
    pinMode(pinoLedAmarelo, LOW);
    pinMode(pinoLedVerde2, LOW);
  }

void loop()
  {
    verifica_lados();

  }
