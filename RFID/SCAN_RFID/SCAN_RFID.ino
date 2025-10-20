#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// הגדרת חיבורים של קורא ה-RFID
#define RST_PIN 9    // Pin לחיבור RST
#define NSS_PIN 10   // Pin לחיבור NSS (Chip Select)

// יצירת אובייקט עבור קורא ה-RFID
MFRC522 mfrc522(NSS_PIN, RST_PIN);

// יצירת אובייקט מנוע סרוו
Servo myservo;

// הגדרת מזהה כרטיס RFID חוקי (שכמובן תוכל לשנות לפי הצורך)
String allowedCardID = "a3a14c1c";  // הכנס כאן את המזהה של הכרטיס שברצונך לאמת

void setup() {
  // אתחול יציאות
  Serial.begin(9600);  // יציאת Serial לצורך הדפסת תוצאות
  SPI.begin();         // התחלת תקשורת SPI
  mfrc522.PCD_Init();  // אתחול קורא ה-RFID
  myservo.attach(6);   // חיבור מנוע סרוו לפין 6

  // הצגת הודעה ראשונית
  Serial.println("Ready to scan RFID card...");
}

void loop() {
  // אם יש כרטיס חדש שנמצא
  if (mfrc522.PICC_IsNewCardPresent()) {
    // אם כרטיס נמצא וקראנו את המזהה שלו
    if (mfrc522.PICC_ReadCardSerial()) {
      String cardID = "";
      
      // יצירת מחרוזת מזהה כרטיס
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        cardID += String(mfrc522.uid.uidByte[i], HEX);
      }
      
      // הדפסת מזהה הכרטיס
      Serial.print("Card UID: ");
      Serial.println(cardID);

      // אם המזהה תואם ל-ID המותר
      if (cardID == allowedCardID) {
        Serial.println("Card is allowed. Turning the servo...");
        
        // פתיחת מנוע סרוו (למשל, לסיבוב של 90 מעלות)
        myservo.write(90);  // סיבוב של 90 מעלות
        delay(2000);        // המתן 2 שניות

        // חזרה למצב התחלתי
        myservo.write(0);   // סיבוב חזרה ל-0 מעלות
        delay(1000);        // המתן 1 שניה לפני קריאה נוספת
      } else {
        Serial.println("Card is not allowed.");
      }

      // סיום קריאת כרטיס
      mfrc522.PICC_HaltA();
    }
  }
}

   
   
   

 
  
