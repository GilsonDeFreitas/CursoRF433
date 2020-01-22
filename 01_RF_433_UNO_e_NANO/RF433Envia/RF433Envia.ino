//RF433, RF315 Arduino UNO, Nano -> Receptor(GND, 5V, 11(data) ), Transmissor (GND, 3.5V a 12V, 12(data) )
//RF433 Esp8266-12E -> Receptor (GND, 5V, D4)
//RF433 Esp8266-12E -> Transmissor (GND, Vin, D2)
//RF433 SuperHeterodyne Receptor (3V a 5V)
//RF433 SuperHeterodyne Transmissor (2V a 3.6V)

/*
 Autor: Gilson de Freitas
 Contato: 66-9-9998-6062
 Rondonópolis - MT
 Link do Curso de Programação: https://www.hotmart.com/product/arduino-referencia-de-programacao/J7636476D
*/
#include <VirtualWire.h>
#define pinRF  12 // Arduino uno 12

unsigned long MAE    = 100000;//6 digitos
unsigned long FILHA1 = 100001;//6 digitos
unsigned long FILHA2 = 100002;//6 digitos
unsigned long FILHA3 = 100003;//6 digitos
unsigned long TODAS  = 111111;//6 digitos

byte bt1 = 2;
byte bt2 = 3;
byte bt3 = 4;
byte bt4 = 5;

struct tipoPacote
{
  unsigned long PlacaMae;
  unsigned long PlacaFilha;
  int Pino;
  int Valor;
  int Variavel;  
  float Dados;
};

tipoPacote pacote; 

void setup()
{
  pinMode(bt1,INPUT);
  pinMode(bt2,INPUT);
  pinMode(bt3,INPUT);
  pinMode(bt4,INPUT);
  
  vw_set_tx_pin(pinRF);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  Serial.begin(9600);  //Arduino Uno
}

void enviarRF(unsigned long PlacaMae, unsigned long PlacaFilha, int Pino, int Valor, int Variavel, float Dados)
{
  pacote.PlacaMae = PlacaMae;
  pacote.PlacaFilha = PlacaFilha;
  pacote.Pino = Pino;
  pacote.Valor = Valor;
  pacote.Variavel = Variavel;
  pacote.Dados = Dados;

  //Codifiga o pacote para envio
  vw_send((uint8_t *)&pacote, sizeof(pacote));
  vw_wait_tx();  
}

void loop()
{
  if (digitalRead(bt1) == HIGH)
  {
    enviarRF(MAE, FILHA1, 13, 1, 1, 38.3);
    delay(300);
  }

  if (digitalRead(bt2) == HIGH)
  {
    enviarRF(MAE, FILHA2, 13, 1, 2, 38.4);
    delay(300);
  }
  
  if (digitalRead(bt3) == HIGH)
  {
    enviarRF(MAE, FILHA3, 13, 1, 3, 38.5);
    delay(300);
  }
  
  if (digitalRead(bt4) == HIGH)
  {
    enviarRF(MAE, TODAS, 13, 0, 4, 38.6);
    delay(300);
  }
}
