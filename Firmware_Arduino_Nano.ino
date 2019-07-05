//**********************************************************************************AUTOMAÇÃO OFICINA MAKER********************************************************************//
//******************DECLARAÇÃO DE VARIAVEIS E INCLUSÃO DA BIBLIOTECA**************//
#define pinRele 11
#define pinrele2 10
#define  button A0

#include <SoftwareSerial.h>
SoftwareSerial btSerial(0, 1); // RX, TX
 
void setup() {
//**************DEFINIÇÃO DAS SAIDAS E ENTRADAS DO RELÉ***************/        
  pinMode(button, INPUT);    

  pinMode(pinRele, OUTPUT);
  pinMode(pinrele2, OUTPUT);
  digitalWrite(pinRele, HIGH);
  digitalWrite(pinrele2, HIGH);
  btSerial.begin(9600); 
}
//*********************DECLARAÇÃO DAS VARIAVEIS DE ESTADO DO BOTÃO RELÉ E BLUETOOTH*************************/
boolean estadobotao;
boolean statusRele1 =LOW; 
boolean statusRele2 = LOW; 
String btComando;

void loop(){
//*******************VERIFICAÇÃO DA PORTA DO BOTÃO********************//
estadobotao = digitalRead(button);   
Serial.println (estadobotao);

//*******************CONDIÇÃO DE COMANDO DO BOTÃO COM O BLUETOOTH NÃO CONECTADO******************//
   if (estadobotao == 0){    
       digitalWrite(pinrele2, !statusRele2); 
       statusRele2=!statusRele2;
       delay(500);
         Serial.println (" BluetoothConectadoForaDoWhile");
         Serial.println ("-------------------------------");
         Serial.println (estadobotao);
         Serial.println ("*******************************");             
    }               

//*******************CONDIÇÃO DE COMANDO COM BOTÃO E O BLUETOOTH  CONECTADO******************//  
    while (btSerial.available()) {
           Serial.println ("BluetoothConectadoDentroDoWhile");
           Serial.println ("--------------------------------");
           Serial.println (estadobotao);
       
//*******************VERIFICAÇÃO DE TRASMISSAO E RECEPÇÃO DO BLUETOOTH E EXECUÇÃO DE COMANDO*****************//
             char comandoRec = btSerial.read();
             btComando += char( comandoRec );
             Serial.print(comandoRec);
 
               if (comandoRec == ';') {
                  if (btComando == "B1;") {
                      statusRele1=!statusRele1;
                      digitalWrite(pinRele, statusRele1);
                   }
                  if (btComando == "B2;") {
                      statusRele2=!statusRele2;
                      digitalWrite(pinrele2, statusRele2);
                   }
                       btComando = "";  
          
               }   

    }
}
