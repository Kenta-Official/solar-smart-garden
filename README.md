# 🌱 TM1637 Soil Moisture Controller

ระบบตรวจวัดความชื้นดินพร้อมแสดงผลบน **TM1637 4-Digit Display** และควบคุมปั๊มน้ำแบบอัตโนมัติด้วย **Relay Module** ใช้ร่วมกับเซนเซอร์ความชื้นดินบน Arduino

โปรเจกต์นี้เหมาะสำหรับ Smart Garden, ระบบรดน้ำอัตโนมัติ หรือการทดลองทางอิเล็กทรอนิกส์ทั่วไป

---

## 📦 Features

* อ่านค่าความชื้นดินแบบ Real-time
* แสดงผลเปอร์เซ็นต์ความชื้นพร้อมทศนิยม 1 ตำแหน่งบน TM1637
* ควบคุมรีเลย์เปิด–ปิดปั๊มน้ำอัตโนมัติ
* แสดงผล Debug ผ่าน Serial Monitor
* ใช้งานง่าย ติดตั้งเร็ว

---

## 🛠 Hardware Requirements

* Arduino (Uno / Mega / Nano)
* Soil Moisture Sensor (Analog)
* TM1637 4-Digit 7-Segment Display
* Relay Module 5V
* สาย Jumper
* ปั๊มน้ำ หรือโหลดที่ต้องการควบคุม

---

## 🔌 Wiring Diagram

| Device               | Pin                |
| -------------------- | ------------------ |
| Soil Moisture Sensor | A1                 |
| Relay Module         | D2                 |
| TM1637 CLK           | D6                 |
| TM1637 DIO           | D7                 |
| 5V, GND              | ใช้ร่วมกับ Arduino |

---

## 📄 Code Example

```cpp
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

  int displayValue = (int)(moisture_percentage * 100); // เช่น 45.3% → 453

  display.showNumberDecEx(displayValue, 0b01000000, true); // จุดทศนิยมระหว่างหลักที่สองกับสาม

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
```

---

## ⚙️ How It Works

* Arduino อ่านค่าความชื้นจากเซนเซอร์แบบ Analog (0–1023)
* ถูกแปลงเป็นเปอร์เซ็นต์ (ยิ่งค่าต่ำ → ชื้นมาก)
* TM1637 จะแสดงค่าแบบมีทศนิยม 1 ตำแหน่ง เช่น 45.3%
* ถ้าความชื้น ≤ **25%** → รีเลย์เปิดปั๊มน้ำ
* ถ้า > 25% → ปั๊มน้ำหยุดทำงาน

---

## 📁 .gitignore (แนะนำ)

```
# Arduino build files
*.ino.cpp
*.o
*.elf
*.bin
*.eep
*.hex

# VSCode settings
.vscode/

# Mac system files
.DS_Store

# Backup and temporary files
*~
*.swp
*.tmp
```
