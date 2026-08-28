#include <DHT.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <ESP32Time.h>


#define LED 25
#define BOTON_SUMA 35
#define BOTON_RESTA 34
#define DHTPIN 23
#define DHTTYPE DHT11
#define SENSORLUZ
#define SENSORGAS


#define PIN_SDA 21
#define PIN_SCL 22


DHT dht(DHTPIN, DHTTYPE);
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, PIN_SCL, PIN_SDA);
ESP32Time rtc;

typedef enum {
  P1,
  EP1,
  P2,
  MAS_GMT,
  MEN_GMT,
  EP2,
  P3,
  MAS_VAR,
  MEN_VAR
  EP3
} estados_t;


estados_t Estado = P1;


void setup() {
  // put your setup code here, to run once:
}


void loop() {
  //Aca pobar usando un "float gas = lecturaGas();" y asi, y dsp utilizar
  switch (Estado) {
    case P1:
      mostrarP1();
      if (digitalRead(SW1) == LOW) {
        Estado = EP1;
      }
      break;
    case EP1:
      if (digitalRead(SW1) == HIGH) {
        Estado = P2;
      }
      break;
    case P2:
      mostrarP2();
      if (digitalRead(SW1) == LOW) {
        Estado = MAS_GMT;
      }
      if (digitalRead(SW2) == LOW) {
        Estado = MEN_GMT;
      }
      break;
    case MAS_GMT:
      if (digitalRead(SW1) == HIGH) {
        Estado = P2;
        GMT = +;
      }
      if (digitalRead(Sw2) == LOW) {
        Estado = EP2;
      }
      break;
    case MEN_GMT:
      if (digitalRead(SW2) == HIGH) {
        Estado = P2;
        GMT = -;
      }
      if (digitalRead(SW1) == LOW) {
        Estado = EP2;
      }
      break;
    case EP2:
    	if (digitalRead(SW1) == HIGH && digitalRead(SW2) == HIGH){
    	  Estado = P3;
      }
      break;

    case P3:
      mostrarP3();
      if (digitalRead(SW1) == LOW){
        Estado = MAS_VAR;
      }
      if (digitalRead(SW2) == LOW){
        Estado = MEN_VAR;
      } 
      break;

    case MAS_VAR:
      if (digitalRead(SW1) == HIGH){
        Estado = P3;
        ValUmbral = +;
      }  
      if (digitalRead(SW2) == LOW)
        Estado = EP3;  
      }
      break;
    case MEN_VAR:
      if (digitalRead(SW2) == HIGH){
        Estado = P3;
        ValUmbral = - ;
      }
      if (digitalRead(SW1) == LOW){
        Estado = EP3
      }
      break;
    case EP3:
      if (digitalRead(SW1) == HIGH && digitalRead(SW2) == HIGH){
        Estado = P1;
      }
      break;
  }
}


void mos

float lecturaTemp() {
  float temp = dht.readTemperature();
  return temp;
}


int lecturaLuz() {
  int luz = analogRead(SENSORLUZ);
  return luz;
}


float lecturaHume() {
  float humedad = dht.readHumidity();
  return humedad;
}


int lecturaGas() {
  int gas = analogRead(SENSORGAS);
  return gas;
}


float lecturaOpto() {}


float lecturaCorr() {}


float lecturaHumana() {}



