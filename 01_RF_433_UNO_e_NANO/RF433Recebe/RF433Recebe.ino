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
#define pinRF 12

unsigned long MAE   = 100000;//6 digitos
unsigned long Filha = 100002;//6 digitos
unsigned long TODAS = 111111;//6 digitos

int led = 13;

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
uint8_t buf[sizeof(pacote)];
uint8_t buflen = sizeof(pacote);
 
void setup()
{
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  vw_set_rx_pin(pinRF); // Define o pino 12 do Arduino como entrada de dados do receptor
  vw_setup(2000);       // Bits por segundo
  vw_rx_start();        // Inicializa o receptor
}
 
void loop()
{  
  if ( vw_have_message() )
  {
    //Decodifica o pacote recebido
    vw_get_message(buf, &buflen);
    memcpy(&pacote,&buf,buflen);
    
    Serial.print(" Placa Mae: ");    Serial.print(pacote.PlacaMae);
    Serial.print(", Placa Filha: "); Serial.print(pacote.PlacaFilha);
    Serial.print(", Pino: ");        Serial.print(pacote.Pino);
    Serial.print(", Valor: ");       Serial.print(pacote.Valor);    
    Serial.print(", Variavel: ");    Serial.print(pacote.Variavel);
    Serial.print(", Dados: ");       Serial.println(pacote.Dados);
    
    if ( (pacote.PlacaMae == MAE) & ((pacote.PlacaFilha == Filha) || (pacote.PlacaFilha == TODAS)) )
    {
      //pinMode(pacote.Pino,OUTPUT);
      digitalWrite(pacote.Pino, pacote.Valor);
    }
  }
}
