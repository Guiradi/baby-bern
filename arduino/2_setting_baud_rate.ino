// Programa: Trocando a baud rate padrão por 9600

#include <SoftwareSerial.h>

// RX pino 2, TX pino 3
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
  esp8266.begin(115200); // baud rate padrao do ESP8266
   
  Serial.println("** Verificando conexao **");
  Serial.println();
  delay(2000);
  sendData("AT\r\n", 2000, DEBUG);
  delay(2000);
   
  Serial.println("** Seta ESP8266 baud rate para 9600 **");
  Serial.println();
  delay(2000);
  sendData("AT+UART_DEF=9600,8,1,0,0\r\n", 2000, DEBUG);
  delay(5000);
   
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
 * Com esse código, foi possível setar a baud rate do ESP8266
 * para 9600, entrando em sincronia com o Arduino.
 */