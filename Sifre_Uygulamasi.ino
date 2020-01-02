#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include "Adafruit_MPR121.h"

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

String sifre = "1923";
String hesapla;

void setup() {
  pinMode(4,OUTPUT);
  Serial.begin(9600);
  cap.begin(0x5A);
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("Sifreyi giriniz:");

}
void ses(){
  digitalWrite(4,HIGH);
  delay(100);
  digitalWrite(4,LOW);
  }
void loop() {
  currtouched = cap.touched();

  for (uint8_t i = 0; i <=9; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      hesapla = hesapla += i; lcd.clear(); lcd.print("Sifreyi giriniz:" + hesapla);ses();
    }
    if (hesapla.length() == 4) {
      
      if (hesapla == sifre) {
        lcd.setCursor(0, 1);
        lcd.print("Sifre kabul edildi.");
        delay(1000);
        lcd.clear();
        lcd.print("Sifreyi giriniz:");
      }
      else {
        lcd.setCursor(0, 1);
        lcd.print("Hatali sifre!");
        delay(1000);
        lcd.clear();
        lcd.print("Sifreyi giriniz:");
      }
      hesapla = "";
    }
  }
  lasttouched = currtouched;
  return;
}
