#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>


#define RST_PIN 9    
#define NSS_PIN 10   

MFRC522 mfrc522(NSS_PIN, RST_PIN);  

LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup() {
  Serial.begin(9600);    
  lcd.begin(16, 2);     
  lcd.backlight();       
  
  SPI.begin();           
  mfrc522.PCD_Init();    

  lcd.setCursor(0, 0);   
  lcd.print("Welcome:-)"); 
  delay(5000);            
  lcd.clear();            
}

void loop() {
  // בדיקה אם נמצא כרטיס
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      // הצגת המזהה של הכרטיס על ה-LCD
      String cardID = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        cardID += String(mfrc522.uid.uidByte[i], HEX); 
      }
      
      lcd.clear();
      lcd.setCursor(0, 0);    
      lcd.print("Card UID:");  
      lcd.setCursor(0, 1);   
      lcd.print(cardID);      
      delay(3000);           
    }
  }
}

   
   
   

 
  
