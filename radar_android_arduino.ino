#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(10,11);

int pos = 0;
Servo servo_9;
int echoPino = 12; 
int trigPino = 13;
long duracion = 0; 
long distancia = 0; 
int led = 7;
char dato;

void setup()
{
  Serial.begin(9600); 
  BT.begin(9600);
  pinMode(echoPino, INPUT); 
  pinMode(trigPino, OUTPUT); 
  pinMode(led, OUTPUT);
  servo_9.attach(9, 500, 2500);
}

void loop()
{ 
  for (pos = 0; pos <= 180; pos += 1) {
     servo_9.write(pos);
      digitalWrite(trigPino, LOW); 
      digitalWrite(trigPino, HIGH); 
      digitalWrite(trigPino, LOW); 
      duracion = pulseIn(echoPino,HIGH); 
      distancia = duracion / 58; 
      delay(15);
      int i = 0;
      if(distancia <= 10){
        Serial.print("Distancia en cm: ");  
        Serial.println(distancia);
        Serial.print("Posicion: ");  
        Serial.println(pos);
        digitalWrite(led, 1);

        char bufferDistancia[10]=" ";
        
        char* formatoDistancia = "Distancia: %i cm";
        
        sprintf(bufferDistancia, formatoDistancia, distancia);
        
        i++;
        
        BT.println(bufferDistancia);
      }else{
        digitalWrite(led, 0);
      }
  }
  for (pos = 180; pos >= 0; pos -= 1) {
      servo_9.write(pos);
      digitalWrite(trigPino, LOW); 
      digitalWrite(trigPino, HIGH); 
      digitalWrite(trigPino, LOW); 
      duracion = pulseIn(echoPino,HIGH); 
      distancia = duracion / 58; 
      delay(15);
      int i=0;
      if(distancia <= 10){
        Serial.print("Distancia en cm: ");  
        Serial.println(distancia);
        Serial.print("Posicion: ");  
        Serial.println(pos);
        digitalWrite(led, 1);

        char bufferDistancia[10]=" ";
        
        char* formatoDistancia = "Distancia: %i cm";
        
        sprintf(bufferDistancia, formatoDistancia, distancia);
        
        i++;
        
        BT.println(bufferDistancia);
      }else {
        digitalWrite(led, 0);
      }
  }
  
  if (BT.available()){
    dato = BT.read();
    Serial.println(dato);
  }
}