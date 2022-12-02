#include <Keypad.h> // BIBLIOTECA DO TECLADO 
#include <Servo.h>

/*-------------------------|
|---VALORES E DEFINIÇÕES---|
|-------------------------*/

char tecla;  //tecla presisonada

byte contador = 0; /*também faz parte do registro de teclas 
e reseta o sistema quando chega em 4*/

char entrada[5]; //entrada do usuario
char senha [5] ="2A69" ;

int buzzer = 11; //Atribui o valor 11 a variavel buzzer

const int ROWS = 4; //instancia linhas
const int COLS = 4; //instancia Colunas

Servo motor; //instancia o servo
 
//Declaração dos valores do teclado:
char hexaKeys[ROWS][COLS] = { 
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //define pinos de linhas
byte colPins[COLS] = {5, 4, 3, 2}; //define pinos de colunas

//aqui define o teclado, linhas e colunas:
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

/*------------------------|
|----------SETUP----------|
|------------------------*/

void setup (){
   Serial.begin(9600); //permite dar print no console
   Serial.println("teclado 4x4");
   Serial.println("aguardando pressionamento...");
   Serial.println();

 //definindo saidas
   pinMode(13, OUTPUT);
   pinMode(12, OUTPUT);
 //servo
   motor.attach(10, 500, 2500); //conecta o servo
   motor.write(0); //define seu valor base como 0
 }

/*-------------------------|
|----------CODIGO----------|
|-------------------------*/


void loop (){
 

   tecla = customKeypad.getKey(); //pega o valor da tecla
  
  
  if (tecla){ //progressao por teclas
    
    entrada[contador]= tecla;
   
   	++contador;
   
    Serial.print("a tecla pressionada foi ");
    Serial.println(tecla); 
    Serial.print("o total de pressionadas foi ");
    Serial.println(contador);
    Serial.print("a senha digitada foi ");
    Serial.println(entrada);
    Serial.println("-------");
  }

  
  if (contador == 4 ){ //hora que vai checar a senha colocada
    
    if (!strcmp(entrada, senha)) {
  	  Serial.println("SUCESSO"); //colocou a senha certa
      
      while (contador != 0) {
        entrada[contador--] = 0; 
      }
      
      digitalWrite(13, HIGH); //acende o led verde
      motor.write(90); //abre a tranca
      tone(buzzer, 400); //liga o buzzer; 400hz
      
      delay(1000); //espera por um segundo
      noTone(buzzer); //desliga o buzzer
      
      delay(4000); //espera mais antes de fechar a tranca
      motor.write(0); //fecha a tranca
      digitalWrite(13, LOW); //desliga o led verde
      
  	}   
  	 else {
     digitalWrite(12, HIGH); //Liga o led vermelho
     tone(buzzer, 700);//ligando o buzzer; 700hz  
  	 Serial.println("ERRADO! Resetando...");
  	 Serial.println("----");
       
     
  	 while (contador != 0) {
        entrada[contador--] = 0; //reseta o contador e entra
      }
     delay(200); //espera um pouco
     noTone(buzzer);  //Desligando o buzzer.
       
     delay(250);    
     tone(buzzer, 700);/*repete o buzzer para se diferenciar   
     de uma entrada bem sucedida*/
       
     delay(400);
     noTone(buzzer);
       
     delay(650);   
     digitalWrite(12, LOW); //desliga o led vermelho    
     
     Serial.println("Insira a senha....");
    }
  }
} 