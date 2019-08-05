// Programa: Testando conexão com a internet e criando um web server

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
  esp8266.begin(9600);
   
  Serial.println("** Reiniciando o modulo **");
  Serial.println();
  sendData("AT+RST\r\n", 2000, DEBUG);
   
  Serial.println("** Checa versao **");
  Serial.println();
  sendData("AT+GMR\r\n", 2000, DEBUG);
  
  Serial.println("** Setando módulo para Station Mode **");
  Serial.println();
  sendData("AT+CWMODE_CUR=1\r\n", 1000, DEBUG);

  Serial.println("** Conectando-se a rede wireless **");
  Serial.println();
  sendData("AT+CWJAP_CUR=\""REDE"\",\""SENHA"\"\r\n", 10000, DEBUG);
  delay(3000);

  Serial.println("** Mostra o endereco IP **");
  Serial.println();
  sendData("AT+CIFSR\r\n", 1000, DEBUG);

  Serial.println("** Configura para multiplas conexoes **");
  Serial.println();
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);

  Serial.println("** Inicia o web server na porta 80 **");
  Serial.println();
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);
  
   
  Serial.println();
  Serial.println("*** Final ***");
}
 
void loop() {
  // Verifica se o ESP8266 esta enviando dados
  if (esp8266.available())
  {
    if (esp8266.find("+IPD,"))
    {
      delay(300);
      int connectionId = esp8266.read() - 48;

      String webpage = "<head><meta http-equiv=""refresh"" content=""3"">";
      webpage += "</head><h1><u>ESP8266 - Web Server</u></h1><h2>Porta";
      webpage += "Digital 8: ";
      int a = digitalRead(8);
      webpage += a;
      webpage += "<h2>Porta Digital 9: ";
      int b = digitalRead(9);
      webpage += b;
      webpage += "</h2>";

      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      cipSend += "\r\n";

      sendData(cipSend, 1000, DEBUG);
      sendData(webpage, 1000, DEBUG);

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
      closeCommand += "rn";
 
      sendData(closeCommand, 3000, DEBUG);
    }
  }
}
 
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ((time + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.println(response);
  }
  return response;
}
