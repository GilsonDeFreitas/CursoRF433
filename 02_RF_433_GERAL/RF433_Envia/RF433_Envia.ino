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
 
RH_ASK driver; //CRIA O DRIVER PARA COMUNICAÇÃO ARDUINO UNO E NANO: Transmissor no pino 12, Receptor no pino 11
//RH_ASK driver(2000, 2, 4, 5); //CRIA O DRIVER PARA COMUNICAÇÃO ESP8266-12E: Transmissor no pino GPIO 4 (D2), Receptor no pino GPIO 2 (D4)

int tempo = 5000;
void enviaRF(char *msg)
{  
  driver.send((uint8_t *)msg, strlen(msg)); //ENVIA AS INFORMAÇÕES PARA O RECEPTOR (PALAVRA: led)
  driver.waitPacketSent(); //AGUARDA O ENVIO DAS INFORMAÇÕES  
}

void setup()
{
  driver.init(); //INICIALIZA A COMUNICAÇÃO RF DO DRIVER
}

void loop()
{
  enviaRF("|PLACA_MAE_118|FILHA_118_01|3|1|LED|37.11|");// Placa mãe, transmite o comando para a placa Filha 01 ligar o Led 3
  delay(tempo);
  enviaRF("|PLACA_MAE_118|FILHA_118_02|3|1|LED|37.21|");// Placa mãe, transmite o comando para a placa Filha 02 ligar o Led 3
  delay(tempo);
  enviaRF("|PLACA_MAE_118|FILHA_118_03|3|1|LED|37.31|");// Placa mãe, transmite o comando para a placa Filha 03 ligar o Led 3
  delay(tempo);
  enviaRF("|PLACA_MAE_118|FILHA_118|3|0|LED|37.31|");  // Placa mãe, transmite o comando para todas as placa Filhas (01, 02 e 03) desligar os LEDs 3
  delay(tempo);
}
