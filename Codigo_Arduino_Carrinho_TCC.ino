#include <HCSR04.h>        
#include <AFMotor.h>        
#include <SoftwareSerial.h> 
SoftwareSerial bluetooth(A1, A0 ); 

#define FORWARD 2 
#define BACKWARD 1 


AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);


HCSR04 sensorDistancia( A2, A3 ); 
HCSR04 sensorDistanciaa(A4, A5);  
char comando = 0 ;
int distancia;
int distancia2;


void setup() {
  bluetooth.begin(9600); 
  Serial.begin(9600); 


  motor1.setSpeed(255);  
  motor2.setSpeed(255);  
  motor3.setSpeed(255); 
  motor4.setSpeed(255); 

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
}

void loop() {
  
  while (bluetooth.available()) { 
    comando = bluetooth.read(); 
    distancia = sensorDistancia.dist();
    distancia2 = sensorDistanciaa.dist();
    Serial.println(distancia);
    Serial.println("|");
    Serial.println(distancia2);
    
    if(comando == 'F' && distancia >= 20) { 
      moverFrente();
    
    }
    else if (comando == 'B' && distancia2 >= 20) {   
      moverTras();
    }
    else if (comando == 'L') {   
      moverEsquerda();
    }
    else if (comando == 'R') {  
      moverDireita();
    } else { 
      ficarParado();
    }
    bluetooth.print(distancia); 
    bluetooth.print("|");
    bluetooth.print(distancia2); 
    bluetooth.println("|");

  } 
  ; 
}

void moverFrente() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}
void moverTras() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}
void moverDireita() {
  motor3.run(RELEASE);
  motor2.run(BACKWARD);
  motor1.run(RELEASE);
  motor4.run(FORWARD);
}
void moverEsquerda() {
  motor3.run(RELEASE);
  motor2.run(FORWARD);
  motor1.run(RELEASE);
  motor4.run(BACKWARD);
}
void ficarParado() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}