#include <TM1637Display.h>

const int sensor_pin = A1; // Soil moisture sensor output pin
int Relay1 = 2;            // Relay control pin
#define CLK 6
#define DIO 7

TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  pinMode(Relay1, OUTPUT);
  digitalWrite(Relay1, HIGH);
  display.setBrightness(7); // Brightness level (0-7)
}

void loop() {
  int sensor_analog = analogRead(sensor_pin);
  float moisture_percentage = (100 - ((sensor_analog / 1023.0) * 100));

  // แปลงค่าเป็นตัวเลขที่มีทศนิยม 1 ตำแหน่ง
  int displayValue = (int)(moisture_percentage * 100); // เช่น 45.3% → 453

  // แสดงค่าบน TM1637 โดยมีจุดทศนิยม
  display.showNumberDecEx(displayValue, 0b01000000, true); // จุดทศนิยมระหว่างหลักที่สองกับสาม

  // ควบคุมรีเลย์ตามค่าความชื้น
  if (moisture_percentage <= 25) {
    digitalWrite(Relay1, LOW);  // เปิดรีเลย์ (เปิดปั๊มน้ำ)
  } else {
    digitalWrite(Relay1, HIGH); // ปิดรีเลย์
  }
Serial.print("Moisture Percentage = "); 
Serial.print(moisture_percentage); 
Serial.print("%\n\n");
  delay(1000);
}