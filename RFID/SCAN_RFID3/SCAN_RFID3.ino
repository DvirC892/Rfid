#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define RFID pins
#define RST_PIN 9
#define SS_PIN 10

// Define LEDs and buzzer pins
#define RED_LED_PIN 7
#define YELLOW_LED_PIN 4
#define BUZZER_PIN 8

// Define ultrasonic sensor pins
#define TRIG_PIN 2
#define ECHO_PIN 3

MFRC522 mfrc522(SS_PIN, RST_PIN);   // RFID reader
Servo myservo;                      // Servo
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD screen

String allowedCardID = "13ad68fa";  // Allowed card ID

unsigned long previousMillis = 0;   // For timing distance measurement
const long interval = 500;          // Interval for distance reading (ms)

int currentDistance = 0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  myservo.attach(6);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ready to scan");
}

void loop() {
  // Measure distance every 'interval' ms
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    currentDistance = getDistance();
    Serial.print("Distance: ");
    Serial.print(currentDistance);
    Serial.println(" cm");
  }

  // RFID card present?
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      String cardID = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        cardID += String(mfrc522.uid.uidByte[i], HEX);
      }

      lcd.clear();
      lcd.setCursor(0, 0);

      if (cardID == allowedCardID) {
        lcd.print("Card Accepted");

        tone(BUZZER_PIN, 1100, 200);
        delay(200);
        tone(BUZZER_PIN, 1500, 100);
        delay(100);
        noTone(BUZZER_PIN);

        digitalWrite(YELLOW_LED_PIN, HIGH);
        delay(1000);
        digitalWrite(YELLOW_LED_PIN, LOW);

        Serial.print("Distance on card scan: ");
        Serial.print(currentDistance);
        Serial.println(" cm");

        if (currentDistance <= 15) {
          myservo.write(0);  // Open servo
          delay(100);
           int scandistance = 0;
          // Wait while object is near
          while (scandistance <= 15) {
            Serial.print("Distance on card scan: ");
            scandistance = getDistance();
            Serial.print(scandistance);
            Serial.println(" cm");
            delay(500);
          }

          delay(2000);
          myservo.write(90);   // Close servo
        }

        delay(2000);
      } else {
        lcd.print("Access Denied");
        tone(BUZZER_PIN, 500, 2000);
        digitalWrite(RED_LED_PIN, HIGH);
        delay(2000);
        digitalWrite(RED_LED_PIN, LOW);
        delay(2000);
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ready to scan");

      mfrc522.PICC_HaltA();
    }
  }
}

// Ultrasonic distance measurement function
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}
