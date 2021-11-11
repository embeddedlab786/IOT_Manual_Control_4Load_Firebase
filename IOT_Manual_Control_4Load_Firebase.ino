/* 
 https://arduino.esp8266.com/stable/package_esp8266com_index.json
 */

#include <ESP8266WiFi.h> 
#include <FirebaseESP8266.h>

#define ssid "M.Ansar"  //WiFi SSID
#define password "78612345"  //WiFi Password
#define FIREBASE_HOST "------------" //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "----------------" //Your Firebase Auth Token

FirebaseData firebaseData;

// define the GPIO connected with Relays and switches
#define Relay1  D0 //GPIO 16
#define Relay2  D1 //GPIO 5
#define Relay3  D2 //GPIO 4
#define Relay4  D3 //GPIO 0

#define Switch1 10 //SD3
#define Switch2 9  //SD2
#define Switch3 12 //D5
#define Switch4 14 //D6

#define wifiLed D4 //GPIO 2

int load1=1, load2=1, load3=1, load4=1, Power;

void setup() {  
Serial.begin(9600);
  
pinMode(Relay1, OUTPUT); digitalWrite(Relay1, HIGH);  
pinMode(Relay2, OUTPUT); digitalWrite(Relay2, HIGH);
pinMode(Relay3, OUTPUT); digitalWrite(Relay3, HIGH);
pinMode(Relay4, OUTPUT); digitalWrite(Relay4, HIGH);

pinMode(wifiLed, OUTPUT); 

pinMode(Switch1, INPUT_PULLUP);
pinMode(Switch2, INPUT_PULLUP);
pinMode(Switch3, INPUT_PULLUP);
pinMode(Switch4, INPUT_PULLUP);
  
WiFi.begin (ssid, password);
Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
delay(100);
}

void loop() {
  
if (WiFi.status() != WL_CONNECTED){ 
    //Serial.println("WiFi Not Connected");
    digitalWrite(wifiLed, HIGH); //Turn off WiFi LED
  }
  else{ 
    //Serial.println("WiFi Connected");
    digitalWrite(wifiLed, LOW); //Turn on WiFi LED
}
  
Switch_Read();
if(Firebase.get(firebaseData,"/P1")) {
 if (firebaseData.dataType() == "string") {
 Power = firebaseData.stringData().toInt();
 }
}
Relays(); 

Switch_Read();
if(Firebase.get(firebaseData,"/L1")) {
 if (firebaseData.dataType() == "string") {
 load1 = firebaseData.stringData().toInt();
 }
}
Relays(); 

Switch_Read();
if(Firebase.get(firebaseData,"/L2")) {
 if (firebaseData.dataType() == "string") {
 load2 = firebaseData.stringData().toInt();
 }
}
Relays(); 

Switch_Read();
if(Firebase.get(firebaseData,"/L3")) {
 if (firebaseData.dataType() == "string") {
 load3 = firebaseData.stringData().toInt();
 }
}
Relays(); 

Switch_Read();
if(Firebase.get(firebaseData,"/L4")) {
 if (firebaseData.dataType() == "string") {
 load4 = firebaseData.stringData().toInt();
  }
 }
Relays(); 
 
}



void Switch_Read(){
     
     if(digitalRead(Switch1) == LOW){Power=0;
     update_power_status();
      load1 = !load1;
      Relays(); 
if(Firebase.setString(firebaseData, "/L1", String(load1))){
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }else{
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }   
      delay(300); 
  }
else if(digitalRead(Switch2) == LOW){Power=0;
      update_power_status();
      load2 = !load2;
      Relays(); 
if(Firebase.setString(firebaseData, "/L2", String(load2))){
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }else{
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }  
 delay(300);
}
    
else if(digitalRead(Switch3) == LOW){Power=0;
      update_power_status();
      load3 = !load3;
      Relays();
if(Firebase.setString(firebaseData, "/L3", String(load3))){
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else{
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  } 
  delay(300);
 }
 
else if(digitalRead(Switch4) == LOW){Power=0;
      update_power_status();
      load4 = !load4;
      Relays();     
if(Firebase.setString(firebaseData, "/L4", String(load4))){
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
 }else{
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
delay(300);
 }
}


void update_power_status(){
if(Firebase.setString(firebaseData, "/P1", String(Power))){
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
}else{
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
}   
}

void Relays(){  
if(Power==0){
digitalWrite(Relay1, load1);  
digitalWrite(Relay2, load2);
digitalWrite(Relay3, load3);
digitalWrite(Relay4, load4);
}else{
digitalWrite(Relay1, HIGH);  
digitalWrite(Relay2, HIGH);
digitalWrite(Relay3, HIGH);
digitalWrite(Relay4, HIGH);  
 }
}
