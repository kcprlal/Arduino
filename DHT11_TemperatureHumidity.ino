#include <Arduino.h>
#define dht 4

void setupDHT(){
  pinMode(dht, OUTPUT);
  digitalWrite(dht, HIGH);
}

void Start(){
  pinMode(dht,OUTPUT);
  digitalWrite(dht,LOW);
  delay(18);
  digitalWrite(dht,HIGH);
  delayMicroseconds(40);
  pinMode(dht,INPUT);
}

void readData(int8_t* data){
  int pulselength;
  Start();
  delayMicroseconds(160);
  for(int i = 0;i<5;++i){
    for(int j = 0; j<8;++j){
      if(pulseIn(dht,HIGH)<30){
        data[i]|=(0<<7-j);
      }
      else {
        data[i]|=(1<<7-j);
        delayMicroseconds(40);
      }
    }
  }
  pinMode(dht,OUTPUT);
  digitalWrite(dht,HIGH);
}

void readTH(int8_t* temperature, int8_t* humidity, int8_t* data){
  humidity[0]=data[0];
  humidity[1]=data[1];
  temperature[0]=data[2];
  temperature[1]=data[3];
}



void setup() {
  setupDHT();
  Serial.begin(9600);
}
  void loop(){
    int8_t temperature[2]={0,0};
    int8_t humidity[2]={0,0};
    int8_t data[5]={0,0,0,0,0};
    readData(data);
    readTH(temperature, humidity, data);
    Serial.print("temperature: ");
    Serial.print(temperature[0]);
    Serial.print(".");
    Serial.print(temperature[1]);
    Serial.println(" *C");
    Serial.print("humidity: ");
    Serial.print(humidity[0]);
    Serial.print(".");
    Serial.print(humidity[1]);
    Serial.println(" %");
    delay(5000);
  }