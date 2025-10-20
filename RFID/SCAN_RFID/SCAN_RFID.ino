#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN 9   
#define NSS_PIN 10   

MFRC522 mfrc522(NSS_PIN, RST_PIN);

Servo myservo;
String allowedCardID = "a3a14c1c";  

void setup() {
  Serial.begin(9600);  
  SPI.begin();         
  mfrc522.PCD_Init();  
  myservo.attach(6);   

  
  Serial.println("Ready to scan RFID card...");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      String cardID = "";
      
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        cardID += String(mfrc522.uid.uidByte[i], HEX);
      }
      
      Serial.print("Card UID: ");
      Serial.println(cardID);

      if (cardID == allowedCardID) {
        Serial.println("Card is allowed. Turning the servo...");
        myservo.write(90);  
        delay(2000);        
        myservo.write(0);   
        delay(1000);        
      } else {
        Serial.println("Card is not allowed.");
      }

      mfrc522.PICC_HaltA();
    }
  }
}

   
   
   

 
  
