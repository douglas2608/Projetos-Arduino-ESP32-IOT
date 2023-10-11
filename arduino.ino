#include <SoftwareSerial.h>
#include "Ultrasonic.h"
#include <TinyGPS.h>

Ultrasonic sensor1(5,4);
SoftwareSerial arduino(8,9);
SoftwareSerial serialGPS(10, 11); // RX, TX
TinyGPS gps;
unsigned long tempoleitura1 = 0;
unsigned long tempoleitura2 = 0;
unsigned long tempoleitura3 = 0;
unsigned long tempoleitura4 = 0;
String recebido = "";
String recebe;
float lati;
float longe;
float velocidade;
bool estado;
bool alguem;
bool luz;

float distancia = 0;
int direita = 6;

int presenca = 2;
int situacao;
int ldr = A0;
int resultado;
int velocidade_motor;
int leitura;

void setup() {
  arduino.begin(57600);
  serialGPS.begin(9600);
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(ldr,INPUT);
  Serial.println("Arduino-Uno");
  pinMode(presenca, INPUT);
  
}

void loop() {
  //delay(780);
  situacao = digitalRead(presenca);

  if (situacao == HIGH) {
    alguem = true;
    //Serial.println("Movimento Detectado");
    
  }else{
    alguem = false;
     //Serial.println("não Detectado");
  }

  resultado = analogRead(ldr);
  //Serial.println(resultado);
  //delay(1000);
  if (resultado >= 800){
    //Serial.println(" luz apagada");
    luz = false;
    
  }else if (resultado <=799){
    //Serial.println("luz acessa");
    luz = true;
  }
  

  
  if (millis() - tempoleitura3 > 600){
    distancia = sensor1.convert(sensor1.timing(), Ultrasonic::CM);
    Serial.print(distancia);
    Serial.println("::CM");
    tempoleitura3 = millis();
    
  }
  //distancia = sensor1.convert(sensor1.timing(), Ultrasonic::CM);
  //Serial.print(distancia);
  //Serial.println("::CM");
  
  

  if (millis() - tempoleitura2 > 10000){
    leGPS();
    tempoleitura2 = millis();
    
  }
  
  
  
  /* Envia dados
  if (millis() - tempoleitura2 > 10000){
    arduino.println("enviando do arduino para ESP");
    tempoleitura2 = millis();
     
  }*/

  
  //Serial.print("Velocidade (km/h): ");
  //Serial.println(velocidade, 2);
  
  if (millis() - tempoleitura1 >1000){
    
    arduino.print(distancia);
    arduino.print(";");
    arduino.print(lati,6);
    arduino.print(";");
    arduino.print(longe,6);
    arduino.print(";");
    arduino.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    arduino.print(";");
    arduino.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    arduino.print(";");
    arduino.print(velocidade, 2);
    arduino.print(";");
    arduino.print(estado);
    arduino.print(";");
    arduino.print(alguem);
    arduino.print(";");
    arduino.print(luz);
    arduino.print(";");
    arduino.print(velocidade_motor);
    arduino.print(";");
    
    
    
    
    tempoleitura1 = millis();
    
  }
  
  // Recebe dados
  arduino.listen();
  if(arduino.available()){
    //recebido = arduino.readStringUntil('\r');
    recebido = arduino.readStringUntil(';');
    Serial.println(recebe);
    recebe = String(recebido);
    if (recebe =="l"){
      digitalWrite(12,HIGH);
      digitalWrite(13,LOW);
      analogWrite(direita, map(analogRead(velocidade_motor),0,1023,0,255));
      estado = 1;
      //arduino.print("m");
      //arduino.println(';');
      
      
    }
    if (recebe =="d"){
      digitalWrite(12,LOW);
      digitalWrite(13,LOW);
      analogWrite(direita, map(analogRead(velocidade_motor),0,1023,0,255));
      estado = 0;
      //arduino.print("p");
      //arduino.println(';');
      
      
      
    }

    recebido = arduino.readStringUntil(';');
    velocidade_motor =  recebido.toInt();
    map(velocidade_motor,0,100,0,255);
    Serial.println(velocidade_motor);
  //analogWrite(leitura, map(velocidade_motor,0,100,0,255));
  //Serial.println(velocidade_motor);


 /* recebido = arduino.readStringUntil(';');
  velocidade_motor = recebido.toInt();
  leitura = map(velocidade_motor,0,1023,0,255);
  Serial.print(leitura);*/
  
  
  

  //tempoleitura4 = millis();
}
  /*if(arduino.available()){
    
    //recebido = arduino.readStringUntil('\r');
    recebido = arduino.readStringUntil(';');
    Serial.println(recebido);
    recebe = String(recebido);
    if (recebe =="l"){
      digitalWrite(12,HIGH);
      digitalWrite(13,LOW);
      analogWrite(direita,255);
      estado = 1;
      //arduino.print("m");
      //arduino.println(';');
      
      
    }
    if (recebe =="d"){
      digitalWrite(12,LOW);
      digitalWrite(13,LOW);
      analogWrite(direita,255);
      estado = 0;
      //arduino.print("p");
      //arduino.println(';');
      
      
      
    }
    
    
  }*/
  
 

  /*String recebido = Serial.readStringUntil('\r');
  Serial.println(recebido);
  delay(1000);*/

}

void leGPS() {
unsigned long delayGPS = millis();

   serialGPS.listen();
   bool lido = false;
   while ( (millis() - delayGPS) < 500 ) { 
      while (serialGPS.available()) {
          char cIn = serialGPS.read(); 
          lido = gps.encode(cIn); 
      }

      if (lido) { 
         //float flat, flon;
         unsigned long age;
    
         gps.f_get_position(&lati, &longe, &age);
         /*Serial.print("SAT=");
         Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
         Serial.println(",");
         Serial.print(" PREC=");
         Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
         Serial.println(",");
         Serial.println(lati);
         Serial.println(longe);*/
         velocidade = gps.f_speed_kmph();
         
         

    
         //String urlMapa = "Local Identificado: https://maps.google.com/maps/?&z=10&q=";
         //urlMapa += String(flat,6);
         //urlMapa += ",";
         //urlMapa += String(flon,6);
         //Serial.println(urlMapa);
         /*arduino.print(distancia);
         arduino.print(";");
         arduino.print(lati,6);
         arduino.print(";");
         arduino.print(longe,6);
         //arduino.print(";");*/
         
         
         
         
         break; 
      }
   }   
}
