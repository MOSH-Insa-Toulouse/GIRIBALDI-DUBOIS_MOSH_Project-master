/* DUBOIS Remy 
 * GIRIBALDI Romain
 *                      */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX


//Initialisation
void setup() {
 // pin pour interuption 2 et 3 / AO pin analogique
  pinMode(A0,INPUT);
  pinMode(2,INPUT_PULLUP);
  attachInterrupt(0,handler,FALLING);
  
 //Set the Serial
 Serial.begin(115200); //serial port to computer
 mySerial.begin(57600); //serial port to radio
 Serial.println("INIT");
 delay(100);

  //Reset RN2483
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  delay(500);
  digitalWrite(12, HIGH);
  //wait for the RN2483's startup message
  delay(2000); 
  mySerial.flush();
  delay(500);
  
  //Configuration with Our application/device addresses
  mySerial.println("mac set appeui 70B3D57ED0013167");
  delay(100);
  mySerial.println("mac set appkey 78DC1B6B8CAC9503ED39BC7C5CDF58EB");
  delay(100);
  mySerial.println("radio set freq 868000000");
  delay(100);
  mySerial.println("radio set mod lora");
  delay(100);

  mySerial.println("mac join otaa");
  delay(10000);
  
  // Routine de test 
  /*mySerial.println("mac tx cnf 1 ABCDEF");
  mySerial.println("sys get hweui");
  delay(500);*/
}

// Handler de gestion de l'interruption
void handler(){
  int valeur = analogRead(A0);
  String str = "mac tx cnf 1 " + String(valeur);
  mySerial.println(str);
}

//main
void loop() {
  //Si un message est envoyé par par mySerial donc la puce RN Alors on transmet ce message sur le moniteur série   
  //A l'inverse un message écrit sur le moniteur série est transmis a la puce (envoi de commandes)
  if (mySerial.available()) {
    Serial.println(mySerial.readString());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
 // delay(1000);
  
  
}
