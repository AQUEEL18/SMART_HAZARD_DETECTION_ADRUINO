#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int greenled = 11;
int buzzer = 13;
int sensor = A0;      // gas/smoke sensor
int midThre = 60;     // ABOVE this = MILD   (tune after testing)
int thre = 100;        // ABOVE this = DANGER
int psensor = 2;            
int tsensor = 8;
int flame_pin = HIGH;

int redled = 10;
int fanpin = 9;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(tsensor, INPUT);
  pinMode(psensor, INPUT);
  pinMode(sensor, INPUT);
  pinMode(redled, OUTPUT);
  pinMode(fanpin, OUTPUT);
  digitalWrite(fanpin, LOW);

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("HAZARD MONITOR");
  delay(1000);
  lcd.clear();
}

void loop()
{
  digitalWrite(greenled, HIGH);

  int read = digitalRead(psensor);
  int analogValue = analogRead(sensor);
  flame_pin = digitalRead(tsensor);

  String gasStatus;
  bool gasDanger = false;
  if (analogValue >= thre) {
    gasStatus = "DANGER";
    gasDanger = true;
  } else if (analogValue >= midThre) {
    gasStatus = "MILD";
  } else {
    gasStatus = "SAFE";
  }

  bool flameDanger = (flame_pin == LOW);
  bool personPresent = (read == HIGH);   // PIR = context only, not an alarm trigger

  // ---- only gas and flame can set off the alarm ----
  bool alarm = gasDanger || flameDanger;

  digitalWrite(redled, alarm ? HIGH : LOW);
  digitalWrite(fanpin, alarm ? HIGH : LOW);

  if (alarm) tone(buzzer, 1000);
  else noTone(buzzer);

  String overall = alarm ? "DANGER" : gasStatus;

  lcd.setCursor(0, 0);
  lcd.print("STATUS: ");
  lcd.print(overall);
  lcd.print("   ");
  lcd.setCursor(0, 1);
  lcd.print("GAS:");
  lcd.print(analogValue);
  lcd.print(" P:");
  lcd.print(personPresent ? "Y" : "N");
  lcd.print("     ");

  Serial.print("GAS:"); Serial.print(analogValue);
  Serial.print(" FLAME:"); Serial.print(flameDanger ? "DANGER" : "ok");
  Serial.print(" PIR:"); Serial.print(personPresent ? "YES" : "no");
  Serial.print(" OVERALL:"); Serial.println(overall);

  delay(500);
}