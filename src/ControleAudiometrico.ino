/* Luciano Santos de Jesus - TCC - 22/09/2020
 * Dispositivo de Alarme de Problemas no Setor de Tecnologia 
 * Através de Controle Audiométrico Baseado em Arduíno*/
const int pinoSensorSom_Um = A0;
const int pinoSensorSom_Dois = A9;
int recebeValorSensor = 0;
int valorMaior = 0;
float tensao = 0;
int dB = 0;
int defeito = 0;
int cont = 0;
int estadoRele = 0;
int valor_Dois = 0;
int controleProblema_Um = 1;
int controleProblema_Dois = 1;
int controleProblema_Tres = 1;
int controleProblema_Quatro = 1;

//Bibliotecas
#include <Keyboard.h> // Biblioteca Emulador de Teclado
#define pinPause 21  // Pino Responsável Por Pausar o Envio de Mensagem
#define pinBreck 15 // Pino Responsável Por Parar a Leitura
#define pinDefeito_Um 8 
#define pinDefeito_Dois 7
#define pinDefeito_Tres 6 
#define pinDefeito_Quatro 5

void estadoPause();//Função Para Pausar Leitura
void teclaEnter();//Função Teclado
void nivelSom();


void setup() {
  pinMode(pinPause, INPUT_PULLUP);
  pinMode(pinBreck, INPUT_PULLUP);
  Keyboard.begin(); 
  pinMode(10, OUTPUT);//Pino do Led Verde (Ligado)
  pinMode(16, OUTPUT);//Pino do Led Azul (Pausa Envio de Mensagens)
  pinMode(14, OUTPUT);//Pino do Led Vermelho (Desligado a Leitura de Som)
}

void loop() {
  //digitalWrite(pinDefeito_Um, LOW);  // ligar o Led Verde em nível de tensão alto (LOW)
  
  //Para Facilitar Futuras Cargas
  if (!digitalRead(pinBreck)) {
     estadoPause();
     return;
  }


  //Verifica o estado do pinPause
  if (!digitalRead(pinPause)) {
     digitalWrite(10, LOW); 
     digitalWrite(16, HIGH);
     digitalWrite(14, LOW); 

     if (estadoRele == 0) {
         Keyboard.print(444);//Código Para Pausar o Envio de Mensagem
         teclaEnter();
         delay(45000);//Aguarda o Envio da Mesagem
         estadoRele = 1;
         delay(200);
    } 
     problema();
  } else {
          digitalWrite(10, HIGH);
          digitalWrite(16, LOW);
          digitalWrite(14, LOW);
    if (estadoRele == 1) {//SE A LEITURA DO PINO FOR IGUAL A LOW 
        Keyboard.print(555);//Código Para Retornar o Envio de Mensagem, Caso Estejá a cima do Nível
        teclaEnter();
        delay(45000);//Aguarda o Envio da Mesagem
        estadoRele = 0;
        delay(200);
    }
    problema();
  }
}

void nivelSom() {
  while (cont < 10000) {
      recebeValorSensor = analogRead(pinoSensorSom_Um);
      valor_Dois = analogRead(pinoSensorSom_Dois);
      
     if (valor_Dois>recebeValorSensor){
         recebeValorSensor = valor_Dois;
     }
    
    if (recebeValorSensor > valorMaior) {
        valorMaior = recebeValorSensor; // Quarda o Maior Valor de Leitura durante o Loop
    }
     cont++;
  }

    cont = 0;
    tensao = valorMaior / 1023.0 * 4.54;
    dB = 87.1 * tensao - 144, 4;

  if (dB < 0) {
      dB = 0;
  }

   Keyboard.print(dB);
   teclaEnter();
   
  if (dB > 58||dB < 42) {
      delay(45000);//Aguarda o Envio da Mesagem (Não Faz a Leitora do Nível de Som)
  }

  valorMaior = 0;
  delay(100);
}

// Função Para Envio do Código do Problema Para a Planilha de Excel
void problema(){
 // ***  Problema Um ***
   if (!digitalRead(pinDefeito_Um)&& controleProblema_Um == 1) {
        defeito = 600;// Código 600 = Nobreak Apitando
        Keyboard.print(defeito);
        teclaEnter();
        delay(45000);//Aguarda o Envio da Mesagem (Não Faz a Leitora do Nível de Som)
        controleProblema_Um = 0;
   }else{
          if (digitalRead(pinDefeito_Um) && controleProblema_Um == 0) {
               defeito = 600;// Código 600 = Nobreak Apitando
               Keyboard.print(defeito);
               teclaEnter();
               delay(45000);//Aguarda o Envio da Mesagem (Não Faz a Leitora do Nível de Som)
               controleProblema_Um = 1;
   }else{
    // ***  Problema Dois ***
          if (!digitalRead(pinDefeito_Dois)&& controleProblema_Dois == 1) {
               defeito = 650;// Código 650 = Porta do Rack
               Keyboard.print(defeito);
               teclaEnter();
               delay(45000);//Aguarda o Envio da Mesagem (Não Faz a Leitora do Nível de Som)
               controleProblema_Dois = 0;
     }else{
           if (digitalRead(pinDefeito_Dois) && controleProblema_Dois == 0) {
               defeito = 650;// Código 650 = Porta do Rack
               Keyboard.print(defeito);
               teclaEnter();
               delay(45000);//Aguarda o Envio da Mesagem (Não Faz a Leitora do Nível de Som)
               controleProblema_Dois = 1;
     }else{
 // ***  Problema Três ***
         if (!digitalRead(pinDefeito_Tres)&& controleProblema_Tres == 1) {
              defeito = 700;// Código 700 = Cooler
              Keyboard.print(defeito);
              teclaEnter();
              delay(45000);//Aguarda o Envio da Mesagem (Não Faz a Leitora do Nível de Som)
              controleProblema_Tres = 0;
     }else{
           if (digitalRead(pinDefeito_Tres) && controleProblema_Tres == 0) {
               defeito = 700;// Código 700 = Cooler
               Keyboard.print(defeito);
               teclaEnter();
               delay(45000);//Aguarda o Envio da Mesagem (Não Faz a Leitora do Nível de Som)
               controleProblema_Tres = 1;
     }else{
  // ***  Problema Quatro ***
          if (!digitalRead(pinDefeito_Quatro)&& controleProblema_Quatro == 1) {
              defeito = 750;// Código 750 = HD
              Keyboard.print(defeito);
              teclaEnter();
              delay(45000);//Aguarda o Envio da Mesagem (Não Faz a Leitora do Nível de Som)
              controleProblema_Quatro = 0;
     }else{
           if (digitalRead(pinDefeito_Quatro) && controleProblema_Quatro == 0) {
               defeito = 750;// Código 750 = HD
               Keyboard.print(defeito);
               teclaEnter();
               delay(45000);//Aguarda o Envio da Mesagem (Não Faz a Leitora do Nível de Som)
               controleProblema_Quatro = 1;
     }else{
          delay(2000);
          nivelSom();
         }
        }
       }
      }
     }
    }
   }
  }
 }
 
//Função Teclcado
void teclaEnter() {
  Keyboard.press(KEY_RETURN);    // Pressiona o Enter
  delay(5);                     // Espera 100 milissegundos
  Keyboard.release(KEY_RETURN);//Solta o Enter
}

//Função Para Aguardar (Pause)
void estadoPause() {
  digitalWrite(10, LOW);   // Desliga o LED em nível de tensão baixo181 (LOW)
  digitalWrite(16, LOW);  // Desliga o LED em nível de tensão baixo181 (LOW)
  digitalWrite(14, HIGH);// ligar o LED em nível de tensão alto (HIGH)
}
