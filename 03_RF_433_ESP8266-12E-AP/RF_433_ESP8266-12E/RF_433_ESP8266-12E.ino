//RF433, RF315 Arduino UNO, Nano -> Receptor(GND, 5V, 11(data) ), Transmissor (GND, 3.5V a 12V, 12(data) )
//RF433 Esp8266-12E -> Receptor (GND, 5V, D4)
//RF433 Esp8266-12E -> Transmissor (GND, Vin, D2)
//RF433 SuperHeterodyne Receptor (3V a 5V)
//RF433 SuperHeterodyne Transmissor (2V a 3.6V)

/*
 Autor: Gilson de Freitas
 Contato: 66-9-9998-6062
 Rondonópolis - MT
 Canal do Youtube: CurseAgora -> https://www.youtube.com/playlist?list=PLBN3lYxRDbp2teC_Bl79ajtkqRolPgDqt
*/

#include <RH_ASK.h> //INCLUSÃO DE BIBLIOTECA
#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
 
//RH_ASK driver; //CRIA O DRIVER PARA COMUNICAÇÃO ARDUINO UNO E NANO: Transmissor no pino 12, Receptor no pino 11
RH_ASK driver(2000, 2, 4, 5); //CRIA O DRIVER PARA COMUNICAÇÃO ESP8266-12E:
//(Velocidade = 2000, Receptor no pino GPIO2 (D4), Transmissor no pino GPIO4 (D2), 

//WIFI
/*
  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <WiFiAP.h>
  const char* ssid = "Nome_da_sua_Rede_Wifi";
  const char* password = "Senha_da_sua_Wifi";
  WiFiServer server(80);
*/  
//WIFI

//AP
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
  ESP8266WebServer server;
//AP

/*
byte LED1 = 5;
byte LED2 = 4;
byte LED3 = 0;
byte LED4 = 14;
*/

byte statusled = 0;

//---------------------------------------------------------------
//Our HTML webpage contents in program memory
char MAIN_page[] PROGMEM = R"=====(
<html>
<head>

<meta http-equiv='refresh' content='3'>

<style>
  button{
  font-size:50px;
  }  
table, th, td{
  border: 2px solid black;
  padding: 5px;
  font-size:50px;
}
table {
  border-spacing: 15px;
}

</style>
</head><body>

<table style="width:100%">
  <tr>
    <td>Componente</td>
    <td>Ligar</td>
    <td>Desligar</td>
    <td>Status</td>
  </tr>
  <tr>
    <td>LED 1</td>
    <td><a href="led1on" target="myIframe1"> <button> ON </button> </a></td>
    <td><a href="led1of" target="myIframe1"> <button> OF </button> </a></td>
    <td><iframe name="myIframe1" frameborder="0" scrolling="0" width="100px" height="30px"></iframe></td>
  </tr>	
  <tr>
    <td>LED 2</td>
    <td><a href="led2on" target="myIframe2"> <button> ON </button> </a></td>
    <td><a href="led2of" target="myIframe2"> <button> OF </button> </a></td>
    <td><iframe name="myIframe2" frameborder="0" scrolling="0" width="100px" height="30px"></iframe></td>
  </tr>	
  <tr>
    <td>LED 3</td>
    <td><a href="led3on" target="myIframe3"> <button> ON </button> </a></td>
    <td><a href="led3of" target="myIframe3"> <button> OF </button> </a></td>
    <td><iframe name="myIframe3" frameborder="0" scrolling="0" width="100px" height="30px"></iframe></td>
  </tr>
  <tr>
    <td>LED TODAS</td>
    <td><a href="ledtodason" target="myIframe4"> <button> ON </button> </a></td>
    <td><a href="ledtodasof" target="myIframe4"> <button> OF </button> </a></td>
    <td><iframe name="myIframe4" frameborder="0" scrolling="0" width="100px" height="30px"></iframe></td>
  </tr>
<hr>
</body>
</html>
)=====";

void handleRoot() { String s = MAIN_page; server.send(200, "text/html", s); }

void handleled1on(){     /*digitalWrite(LED1,HIGH);*/ statusled = 1; server.send(200, "text/html", "ON"); enviaRF("|PLACA_MAE_118|FILHA_118_01|3|1|LED|37.11|"); }
void handleled1of(){     /*digitalWrite(LED1,LOW);*/  statusled = 0; server.send(200, "text/html", "OF"); enviaRF("|PLACA_MAE_118|FILHA_118_01|3|0|LED|37.10|"); }

void handleled2on(){     /*digitalWrite(LED2,HIGH);*/ server.send(200, "text/html", "ON"); enviaRF("|PLACA_MAE_118|FILHA_118_02|3|1|LED|37.21|"); }
void handleled2of(){     /*digitalWrite(LED2,LOW);*/  server.send(200, "text/html", "OF"); enviaRF("|PLACA_MAE_118|FILHA_118_02|3|0|LED|37.20|"); }

void handleled3on(){     /*digitalWrite(LED3,HIGH);*/ server.send(200, "text/html", "ON"); enviaRF("|PLACA_MAE_118|FILHA_118_03|3|1|LED|37.31|"); }
void handleled3of(){     /*digitalWrite(LED3,LOW);*/  server.send(200, "text/html", "OF"); enviaRF("|PLACA_MAE_118|FILHA_118_03|3|0|LED|37.30|"); }

void handleledtodason(){ /*digitalWrite(LED4,HIGH);*/ server.send(200, "text/html", "ON"); enviaRF("|PLACA_MAE_118|FILHA_118|3|1|LED|37.31|"); }
void handleledtodasof(){ /*digitalWrite(LED4,LOW);*/  server.send(200, "text/html", "OF"); enviaRF("|PLACA_MAE_118|FILHA_118|3|0|LED|37.30|"); }

void enviaRF(char *msg)
{  
  driver.send((uint8_t *)msg, strlen(msg)); //ENVIA AS INFORMAÇÕES PARA O RECEPTOR (PALAVRA: led)
  driver.waitPacketSent(); //AGUARDA O ENVIO DAS INFORMAÇÕES  
}

void setup(){
//  pinMode(LED1,OUTPUT);
//  pinMode(LED2,OUTPUT);
//  pinMode(LED3,OUTPUT);
//  pinMode(LED4,OUTPUT);

  driver.init(); //INICIALIZA A COMUNICAÇÃO RF DO DRIVER
  Serial.begin(115200);  
  Serial.println();

  WiFi.mode(WIFI_AP);             //Only Access point
  //WiFi.softAP(ssid, password);  //WIFI: Start HOTspot removing password will disable security
  WiFi.softAP("ESP8266", "12345678");//AP

  //http://192.168.4.1  //IPAddress myIP = WiFi.softAPIP();   //Serial.print("Meu IP:");  //Serial.println(myIP);
  server.on("/", handleRoot);      //Chama a página inicial
  server.on("/led1on", handleled1on); server.on("/led1of", handleled1of); // executa o handle
  server.on("/led2on", handleled2on); server.on("/led2of", handleled2of);
  server.on("/led3on", handleled3on); server.on("/led3of", handleled3of);
  server.on("/ledtodason", handleledtodason); server.on("/ledtodasof", handleledtodasof);

  server.begin();                  //Start server
}

void loop()
{
  server.handleClient();          //Handle client requests  
  //Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(10);
}
