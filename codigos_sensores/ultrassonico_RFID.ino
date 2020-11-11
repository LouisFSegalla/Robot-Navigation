#include <Ultrasonic.h>
#include <SPI.h>
#include <MFRC522.h>

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


#define SS_PIN 53
#define RST_PIN 5

const int pinoLedVerde = 6;
const int pinoLedVermelho = 3;

MFRC522 rfid(SS_PIN, RST_PIN);  // Create MFRC522 instance.

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

void verifica_libera(){
   if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) //VERIFICA SE O CARTÃO PRESENTE NO LEITOR É DIFERENTE DO ÚLTIMO CARTÃO LIDO. CASO NÃO SEJA, FAZ
    return; //RETORNA PARA LER NOVAMENTE
 
  /***INICIO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();
  /***FIM DO BLOCO DE CÓDIGO RESPONSÁVEL POR GERAR A TAG RFID LIDA***/
 
  Serial.print("Identificador (UID) da tag: "); //IMPRIME O TEXTO NA SERIAL
  Serial.println(strID); //IMPRIME NA SERIAL O UID DA TAG RFID
 
   if (strID.indexOf("66:38:0A:F8") >= 0){
    // Serial.println("Tag liberada");
    digitalWrite(pinoLedVerde, HIGH); //LIGA O LED VERDE
     delay(2000); //INTERVALO DE 4 SEGUNDOS
     digitalWrite(pinoLedVerde, LOW); //DESLIGA O LED VERDE
        

   }
   else{
      //Serial.println("You shall not pass");
     digitalWrite(pinoLedVermelho, HIGH); //LIGA O LED VERDE
     delay(2000); //INTERVALO DE 4 SEGUNDOS
     digitalWrite(pinoLedVermelho, LOW); //DESLIGA O LED VERDE

    } 

  rfid.PICC_HaltA(); //PARADA DA LEITURA DO CARTÃO
  rfid.PCD_StopCrypto1(); //PARADA DA CRIPTOGRAFIA NO PCD
  }

void setup()
  {
    
  Serial.begin(9600);
  
   SPI.begin(); //INICIALIZA O BARRAMENTO SPI
  rfid.PCD_Init(); //INICIALIZA MFRC522
  pinMode(pinoLedVerde, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLedVerde, LOW); //LED INICIA DESLIGADO

   pinMode(pinoLedVermelho, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLedVermelho, LOW); //LED INICIA DESLIGADO
  pinMode(pinoLedVerde2, OUTPUT);
  pinMode(pinoLedAmarelo, OUTPUT);
  pinMode(pinoLedAzul, OUTPUT);
   pinMode(pinoLedAzul, LOW);
    pinMode(pinoLedAmarelo, LOW);
    pinMode(pinoLedVerde2, LOW);
  }

void loop() {
  // put your main code here, to run repeatedly:
  verifica_libera();
  verifica_lados();
}
