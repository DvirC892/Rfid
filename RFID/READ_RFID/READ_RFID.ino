#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>


#define RST_PIN 9    
#define NSS_PIN 10   

MFRC522 mfrc522(NSS_PIN, RST_PIN);  // יצירת אובייקט של קורא RFID

// יצירת אובייקט LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // כתובת I2C של LCD 0x27, 16 עמודות ו-2 שורות

void setup() {
  Serial.begin(9600);    // התחלת יציאת serial
  lcd.begin(16, 2);      // התחלת המסך LCD עם 16 עמודות ו-2 שורות
  lcd.backlight();       // הדלקת תאורה אחורית במסך LCD
  
  SPI.begin();           // התחלת תקשורת SPI
  mfrc522.PCD_Init();    // אתחול קורא ה-RFID

  lcd.setCursor(0, 0);   // הצבת הסמן בתור הראשון
  lcd.print("Welcome:-)"); // הדפסת כותרת במסך
  delay(5000);            // השהיה של שניה
  lcd.clear();            // ניקוי המסך
}

void loop() {
  // בדיקה אם נמצא כרטיס
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      // הצגת המזהה של הכרטיס על ה-LCD
      String cardID = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        cardID += String(mfrc522.uid.uidByte[i], HEX); // יצירת מחרוזת מזהה הכרטיס
      }
      
      lcd.clear();
      lcd.setCursor(0, 0);    // הצבת הסמן בשורה הראשונה
      lcd.print("Card UID:");  // הצגת טקסט
      lcd.setCursor(0, 1);    // הצבת הסמן בשורה השנייה
      lcd.print(cardID);      // הצגת המזהה של הכרטיס
      delay(3000);            // הצגת המידע למשך 3 שניות
    }
  }
}

   
   
   

 
  
