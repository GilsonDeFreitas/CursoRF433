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
#include <VirtualWire.h>
#define pinRF  12 // Arduino uno 12

unsigned long MAE    = 100000;//6 digitos
unsigned long FILHA1 = 100001;//6 digitos
unsigned long FILHA2 = 100002;//6 digitos
unsigned long FILHA3 = 100003;//6 digitos
unsigned long TODAS  = 111111;//6 digitos

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
  enviarRF(MAE, FILHA1, 10, 1, 1, 38.3);
  delay(1000);

  enviarRF(MAE, FILHA2, 10, 1, 2, 38.4);
  delay(1000);
  
  enviarRF(MAE, FILHA3, 10, 1, 3, 38.5);
  delay(1000);

  enviarRF(MAE, TODAS, 10, 0, 4, 38.6);
  delay(1000);
}
