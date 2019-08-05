// Programa: Testando o ESP8266 com baud rate setado para 9600

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
  esp8266.begin(9600); // novo baud rate do esp
   
  Serial.println("** Verificando conexao **");
  Serial.println();
  sendData("AT\r\n", 2000, DEBUG);
   
  Serial.println("** Versao de firmware **");
  Serial.println();
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
 * Com esse código foi possível observar um funcionamento correto do módulo
 * com as respostas perfeitas mesmo sem o delay do Arduino entre requests.
 */
