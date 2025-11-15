#include <Wire.h>
#include <LiquidCrystal.h>     // library LCD
#include "RTClib.h"            // library DS3231

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Objek LCD (bukan rtc!)
RTC_DS3231 rtc;                      // Objek RTC

char dataHari[7][12] = {"Ming", "Sen", "Sel", "Rab", "Kam", "Jum", "Sab"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;
float suhu;

byte logo[8] = {
  0b00100, 
  0b01010, 
  0b01010, 
  0b01010, 
  0b01110, 
  0b11111, 
  0b11111, 
  0b01110
  };

void setup () {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(1, logo);
 

  if (!rtc.begin()) {
    Serial.println("RTC Tidak Ditemukan");
    Serial.flush();
    abort();
  }

  // Gunakan salah satu baris di bawah untuk set waktu (upload sekali saja)
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}


void loop () {
  DateTime now = rtc.now();   // <- diperbaiki dari rtc.begin() menjadi rtc.now()

  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day();
  bulan   = now.month();
  tahun   = now.year();
  jam     = now.hour();
  menit   = now.minute();
  detik   = now.second();
  suhu    = rtc.getTemperature();  // fungsi suhu DS3231

  lcd.setCursor(0, 0);
  lcd.print(String() + hari + ",  " + tanggal + "/" + bulan + "/" + tahun);
  lcd.setCursor(0, 1);
  lcd.print(String() + jam + ":" + menit + ":" + detik + "   " + suhu + "C");
  
  lcd.setCursor(10, 1);
  lcd.write((byte)1);

  delay(1000);
}
