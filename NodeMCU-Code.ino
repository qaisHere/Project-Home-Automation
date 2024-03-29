#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define FIREBASE_HOST "iot-home-automation-12987.firebaseio.com"                     
#define FIREBASE_AUTH "h3zbBoDpacWeY6C2GzvqHTzooKwSw8xBEtRi08lJ"       
#define WIFI_SSID "......"             
#define WIFI_PASSWORD "....."        
 
#define Fan D1 //D6
int val1;
 
#define Light D2 //D2
int val2;
 
#define TV D3  //D1
int val3;
 
#define AC D4 //D5
int val4;
 
void setup() 
{
  Serial.begin(115200);                                               
  pinMode(Fan,OUTPUT);
  pinMode(Light,OUTPUT);
  pinMode(TV,OUTPUT);
  pinMode(AC,OUTPUT);
 
  digitalWrite(Fan,HIGH);
  digitalWrite(Light,HIGH);
  digitalWrite(TV,HIGH);
  digitalWrite(AC,HIGH);
 
 
 
  
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());
 
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setInt("S1",0);                     
  Firebase.setInt("S2",0); 
  Firebase.setInt("S3",0); 
  Firebase.setInt("S4",0); 
  
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }
 
void loop() 
{
  if (Firebase.failed())
   {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }
      
  val1=Firebase.getString("S1").toInt();                                        
  
  if(val1==1)                                                             
     {
      digitalWrite(Fan,LOW);
      Serial.println("Fan ON");
    }
    else if(val1==0)                                                      
    {                                      
      digitalWrite(Fan,HIGH);
      Serial.println("Fan OFF");
    }
 
  val2=Firebase.getString("S2").toInt();                                        
  
  if(val2==1)                                                             
     {
      digitalWrite(Light,LOW);
      Serial.println("light  ON");
    }
    else if(val2==0)                                                      
    {                                      
      digitalWrite(Light,HIGH);
      Serial.println("light  OFF");
       }
 
   val3=Firebase.getString("S3").toInt();                                        
  
  if(val3==1)                                                             
     {
      digitalWrite(TV,LOW);
      Serial.println("TV ON");
    }
    else if(val3==0)                                                      
    {                                      
      digitalWrite(TV,HIGH);
      Serial.println("TV OFF");
    }
 
   val4=Firebase.getString("S4").toInt();                                       
  
  if(val4==1)                                                             
     {
      digitalWrite(AC,LOW);
      Serial.println("AC ON");
    }
    else if(val4==0)                                                      
    {                                      
      digitalWrite(AC,HIGH);
      Serial.println("AC OFF");
    }    
}
