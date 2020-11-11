/*
* MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
* The library file MFRC522.h has a wealth of useful info. Please read it.
* The functions are documented in MFRC522.cpp.
*
* Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
* Created by Miguel Balboa (circuitito.com), Jan, 2012.
* Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
* Released into the public domain.
*
* Sample program showing how to read data from a PICC using a MFRC522 reader on the Arduino SPI interface.
*----------------------------------------------------------------------------- empty_skull
* Aggiunti pin per arduino Mega
* add pin configuration for arduino mega
* http://mac86project.altervista.org/
----------------------------------------------------------------------------- Nicola Coppola
* Pin layout should be as follows:
* Signal     Pin              Pin               Pin
*            Arduino Uno      Arduino Mega      MFRC522 board
* ------------------------------------------------------------
* Reset      9                5                 RST  Cinza(PWM)
* SPI SS     10               53                SDA  Branco
* SPI MOSI   11               51                MOSI Laranja
* SPI MISO   12               50                MISO Azul
* SPI SCK    13               52                SCK  Verde
*
* The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com.
*/

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 5

const int pinoLedVerde = 6;
const int pinoLedVermelho = 3;
MFRC522 rfid(SS_PIN, RST_PIN);  // Create MFRC522 instance.

void setup() {
  Serial.begin(9600); //INICIALIZA A SERIAL
  SPI.begin(); //INICIALIZA O BARRAMENTO SPI
  rfid.PCD_Init(); //INICIALIZA MFRC522
  pinMode(pinoLedVerde, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLedVerde, LOW); //LED INICIA DESLIGADO

   pinMode(pinoLedVermelho, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLedVermelho, LOW); //LED INICIA DESLIGADO
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
 
void loop() {
    verifica_libera();
}
