#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // הוספת ספריית LCD

// הגדרת חיבורים של קורא ה-RFID
#define RST_PIN 9    // Pin לחיבור RST
#define NSS_PIN 10   // Pin לחיבור NSS (Chip Select)

// הגדרת הפינים לחיבור המנורות (אדומה וצהובה)
#define RED_LED_PIN 7  // פין למנורה אדומה
#define YELLOW_LED_PIN 4  // פין למנורה צהובה

// הגדרת הפין לחיבור האזעקה (buzzer)
#define BUZZER_PIN 8

// יצירת אובייקט עבור קורא ה-RFID
MFRC522 mfrc522(NSS_PIN, RST_PIN);

// יצירת אובייקט מנוע סרוו
Servo myservo;

// יצירת אובייקט למסך LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // כתובת ה-I2C של המסך (שנה אם יש צורך)

int servoState = 0; // בהתחלה המנוע סגור
String allowedCardID = "13ad68fa";  // הכנס כאן את המזהה של הכרטיס שברצונך לאמת

void setup() {
  SPI.begin();         // התחלת תקשורת SPI
  mfrc522.PCD_Init();  // אתחול קורא ה-RFID
  myservo.attach(6);   // חיבור מנוע סרוו לפין 6
  pinMode(BUZZER_PIN, OUTPUT);  // הגדרת הפין לחיבור האזעקה

  // הגדרת הפינים של המנורות
  pinMode(RED_LED_PIN, OUTPUT);     // מנורה אדומה
  pinMode(YELLOW_LED_PIN, OUTPUT);  // מנורה צהובה

  lcd.begin(16, 2);     // אתחול המסך LCD
  lcd.backlight();      // הדלקת תאורה אחורית למסך
  lcd.setCursor(0, 0);  // הצבת הסמן בתור הראשון
  lcd.print("Ready to scan");  // הצגת הודעה ראשונית במסך
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      String cardID = "";
      
      // יצירת מחרוזת מזהה כרטיס
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        cardID += String(mfrc522.uid.uidByte[i], HEX);
      }
      
      // ניקוי המסך לפני הצגת הודעה חדשה
      lcd.clear();  
      lcd.setCursor(0, 0);  // הצבת הסמן בשורה הראשונה

      // אם המזהה תואם ל-ID המותר
      if (cardID == allowedCardID) {
        lcd.print("Card Accepted");  // הצגת הודעת "כרטיס מאושר"
        
        tone(BUZZER_PIN, 1000, 200);  // צפצוף במהירות 1000Hz למשך 200 מילי-שניות

        // הדלקת מנורה צהובה למשך 2 שניות
        digitalWrite(YELLOW_LED_PIN, HIGH);
        delay(2000);  // המתן 2 שניות
        digitalWrite(YELLOW_LED_PIN, LOW);

        if (servoState == 0) {
          myservo.write(90);  // פותח את המנוע
          servoState = 1;

          delay(5000); // המתן 5 שניות כשהמנוע פתוח
          
          myservo.write(0);  // סוגר את המנוע אחרי 5 שניות
          servoState = 0;
        }

        delay(2000); // המתן 2 שניות לפני חזרה להודעת "Ready to scan"
      } else {
        lcd.print("Access Denied");  // הצגת הודעת "גישה נדחתה"
        tone(BUZZER_PIN, 500, 2000);  // צפצוף ארוך ורציף למשך 2 שניות

        // הדלקת מנורה אדומה למשך 5 שניות
        digitalWrite(RED_LED_PIN, HIGH);
        delay(5000);  // המתן 5 שניות
        digitalWrite(RED_LED_PIN, LOW);

        delay(2000); // המתן 2 שניות לפני חזרה להודעת "Ready to scan"
      }

      // חזרה להודעת "Ready to scan" לאחר 2 שניות
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Ready to scan");

      mfrc522.PICC_HaltA();
    }
  }
}

   
   
   

 
  
