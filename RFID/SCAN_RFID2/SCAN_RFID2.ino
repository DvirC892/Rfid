#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  

#define RST_PIN 9    
#define NSS_PIN 10   
#define RED_LED_PIN 7  
#define YELLOW_LED_PIN 4  

#define BUZZER_PIN 8
MFRC522 mfrc522(NSS_PIN, RST_PIN);
Servo myservo;

LiquidCrystal_I2C lcd(0x27, 16, 2);  

int servoState = 0; 
String allowedCardID = "13ad68fa";  

void setup() {
  SPI.begin();         
  mfrc522.PCD_Init();  
  myservo.attach(6);   
  pinMode(BUZZER_PIN, OUTPUT);  

 
  pinMode(RED_LED_PIN, OUTPUT);     
  pinMode(YELLOW_LED_PIN, OUTPUT);  

  lcd.begin(16, 2);     
  lcd.backlight();     
  lcd.setCursor(0, 0);  
  lcd.print("Ready to scan");  
}

void loop() {
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
        
        tone(BUZZER_PIN, 1000, 200);  

        
        digitalWrite(YELLOW_LED_PIN, HIGH);
        delay(2000);  
        digitalWrite(YELLOW_LED_PIN, LOW);

        if (servoState == 0) {
          myservo.write(90);  
          servoState = 1;

          delay(5000); 
          
          myservo.write(0);  
          servoState = 0;
        }

        delay(2000); 
      } else {
        lcd.print("Access Denied");  
        tone(BUZZER_PIN, 500, 2000);  

        digitalWrite(RED_LED_PIN, HIGH);
        delay(5000);  
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

   
   
   

 
  
