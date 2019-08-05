// Programa: Comandos AT com ESP8266
// Guia do Usuario do ESP8266

#include <SoftwareSerial.h>

//RX pino 2, TX pino 3
/*
 * Adaptador      Arduino
 *    RX      ->   3(TX)
 *    TX      ->   2(RX)
 */
 SoftwareSerial esp8266(2, 3);
 
 #define DEBUG true
 
 void setup()
 {
   Serial.begin(9600);
   esp8266.begin(115200); // baud rate padrao do ESP8266 115200
   
   Serial.println("** Verificando conexao **");
   Serial.println();
   delay(2000);
   sendData("AT\r\n", 2000, DEBUG);
   
   Serial.println("** Versao de firmware **");
   Serial.println();
   delay(2000);
   sendData("AT+GMR\r\n", 2000, DEBUG);
   
   Serial.println();
   Serial.println("*** Final ***");
 }
 
 void loop() {}
 
 String sendData(String command, const int timeout, boolean debug)
 {
    // Envio dos comandos AT para o modulo
    String response = "";
    esp8266.print(command);
    long int time = millis();
    while ((time + timeout) > millis())
    {
      while (esp8266.available())
      {
        // The esp has data so display its output to the serial window
        char c = esp8266.read(); // read the next character.
        response += c;
      }
    }
    if (debug)
    {
      Serial.println(response);
    }
    return response;
 }

/**
 * Fiz alguns testes com esse código e descobri que
 * é possível que como o Arduino está rodando em serial 9600
 * e o ESP8266 está em 115200, o tempo de resposta está em 
 * conflito, causando caracteres mal lidos ou indesejados.
 */