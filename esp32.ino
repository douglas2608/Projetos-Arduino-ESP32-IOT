#include "thingProperties.h"
#include <SoftwareSerial.h>


SoftwareSerial esp(18, 19);

unsigned long tempoleitura1 = 0;
unsigned long tempoleitura2 = 0;
unsigned long tempoleitura3 = 0;
unsigned long tempoleitura4 = 0;
unsigned long tempoleitura5 = 0;
unsigned long tempoleitura6 = 0;
unsigned long tempoleitura7 = 0;
int a = 21;
String teste = "";
String teste3 = "";
float recebe;
double Latitude;
double longetude;
int sat;
float prec;
float velocidade;
int estado;
String motor;
int alguem; 
String pessoa;
int cont = 0;
int luz;
String ambiente;
String liga;
int velocidade_motor;



void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  esp.begin(57600);
  pinMode(21, OUTPUT);
  
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  ir =false;
  motor =" Desligado";
  estado =0;

}
void onMsgChange()  {
  // Add your code here to act upon Msg change
}

void onGpsChange()  {
  // Add your code here to act upon Gps change
}

void onIrChange()  {
  ArduinoCloud.update();
  digitalWrite(a, ir);
  if (ir == HIGH) {
    //liga = "l";
    velocidade_motor = preci;
    esp.print("l");
    esp.print(';');
    //msg = " acionando motores ";
    //delay(400);
    
  }
  
  if (ir ==LOW ){
    //liga = "d";
    velocidade_motor = preci;
    esp.print("d");
    esp.print(';');
   // msg = " Desligando motores ";
   // delay(400);
    
    
    
    


  }
  


}
void onPreciChange(){
 if (preci){
  
  esp.print(";");
  esp.print(preci);
  
    
  }
  
  
}
void loop() {
  ArduinoCloud.update();
  
  
  // Envia dados
  /*if (millis()- tempoleitura2 >10000){
    esp.println("eu sou o ESP32 Falando com arduino");

    
    tempoleitura2 = millis();
    }*/
  // Recebe dados
 

  //Serial.println(msg);

  if (millis() - tempoleitura2 > 8000){
      gps = {Latitude, longetude};
      tempoleitura2 = millis();
      
      
    }
    

  /*if (millis() - tempoleitura7 >= 8000){
     esp.print(preci);
     esp.print(";");
     tempoleitura7 = millis();
    
  }*/
   
    //delay(1000);

    


  /*if (ir == false and estado ==1) {
    ir = true;

  
      
      
   }else if(ir == true and estado ==0){
    ir = false;
      
    }*/

    

  

 /* if (millis() - tempoleitura6 >1000){
    esp.print(preci);  
    
  }*/
  
 
  
    
    
    
  
   
  if (esp.available()) {
    teste = esp.readStringUntil(';'); 
    //Serial.println(teste);
    //ArduinoCloud.update();
    dISTANCIA = teste.toFloat();
    //dISTANCIA = recebe;
    
     

    /*if (recebe >= 30){
      msg = " distancia maior que 30 Centimetros ";
    }else if (recebe < 30 and recebe > 0 ){
      msg = " distancia MENOR que 30 Centimetros";
    }
    //gps = location("-23.578730, -46.817631");*/

    teste = esp.readStringUntil(';');
    if (millis() - tempoleitura3 >= 10000){
      Latitude = teste.toDouble();
      //Serial.println(Latitude);
      tempoleitura3 = millis();
      
      
    }
    //Latitude = teste.toDouble();
    
    teste = esp.readStringUntil(';');
    if (millis() - tempoleitura4 >= 10000){
      longetude = teste.toDouble();
     // Serial.println(longetude);
      tempoleitura4 = millis();
    }
    //longetude = teste.toDouble();
    //Serial.println(longetude);
    
    //gps = {Latitude, longetude};
    
    
    
    teste = esp.readStringUntil(';'); 
    //ArduinoCloud.update();
    if (millis() - tempoleitura5 >= 10000){
      sat = teste.toInt(); 
      tempoleitura5 = millis();     
    }
    //sat = teste.toInt();
   // msg = "Satelite = " + String(sat)+" \n" + "Motor = " +  String(motor);
      
     
    teste = esp.readStringUntil(';');
    //ArduinoCloud.update();
    if (millis() - tempoleitura6 >= 10000){
      prec = teste.toFloat();
      tempoleitura6 = millis();            
    }
    //prec = teste.toFloat();
    //Serial.print(prec);
   // msg = "Precisão metros =  " + String(prec);
    //msg = prec;

    
        
    teste = esp.readStringUntil(';');
    //ArduinoCloud.update();
    velocidade = teste.toFloat();
    if (velocidade <=4 and estado == 0){
      //preci = 0.00;
     }else{
      //preci = velocidade;
    }

    teste = esp.readStringUntil(';');
    estado = teste.toInt();
    if (estado == 1){
      motor = " Ligado";
      ir = true;
      
      
    }else {
      motor = " Desligado";
      ir = false;
      
    }
    teste = esp.readStringUntil(';');
    alguem = teste.toInt();
    if (alguem == 1){
      pessoa = "Pir = movimento Detectado";
      
    }else{
      pessoa = "Pir = Não Detectado";
    }

    teste = esp.readStringUntil(';');
    luz = teste.toInt();
    if (luz == 1){
      ambiente = "luz acessa";
    }else{
      ambiente = "luz apagada";
    }

    teste = esp.readStringUntil(';');
    velocidade_motor = teste.toInt();
    if (velocidade_motor ==0){
      esp.print(";");
      esp.print(preci);
      //velocidade_motor = preci;
    }
    
    
  
    msg = "Satelite = " + String(sat)+" \n" + "Motor = " +  String(motor)+"\n"+"Aceleraçao 0 a 255 =" +String(velocidade_motor)+"\n"+ "Precisão= "+ String(prec)+ "= CM::\M"+"\n"+String(pessoa)+"\n"+"Luz = "+String(ambiente);
    ArduinoCloud.update();
    
    
    


    /*if (teste.equalsIgnoreCase("m")){
      ArduinoCloud.update();
      msg = " Motor Andando";
      ir = true;
     }
    if (teste.equalsIgnoreCase("p")){
      ArduinoCloud.update();
      msg = "Motor parado";
      ir = false;
    }*/

    

    
    
    
  }
     

  
}



// Add your code here to act upon Frente change
