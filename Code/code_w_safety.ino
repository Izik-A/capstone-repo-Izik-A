#include <LiquidCrystal.h>

const int buttonPin = A0;      
const int solenoidPin = 7;     
const int pirPin = 2;          // PIR Sensor Signal Pin
int count = 0;                 

int buttonState = HIGH;
int lastButtonState = HIGH;
int motionDetected = LOW;

// LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(11, 12, 5, 6, 3, 4);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(solenoidPin, OUTPUT);
  pinMode(pirPin, INPUT);      // Set PIR as input
  digitalWrite(solenoidPin, LOW);
  
  lcd.begin(8, 2); 
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("SYSTEM");
  lcd.setCursor(0, 1);
  lcd.print("READY");
  delay(2000); // Give PIR sensor time to "warm up" (calibrate)
}

void loop() {
  buttonState = digitalRead(buttonPin);
  motionDetected = digitalRead(pirPin); // Check for humans!

  // If motion is detected, override everything
  if (motionDetected == HIGH) {
    digitalWrite(solenoidPin, LOW); // Force OFF for safety
    lcd.setCursor(0, 0);
    lcd.print("WARNING ");
    lcd.setCursor(0, 1);
    lcd.print("MOTION! ");
    delay(500); // Small pause to prevent flickering
  } 
  else {
    // Normal operation: If no motion, allow button to work
    lcd.setCursor(0, 0);
    lcd.print("Count:  ");
    lcd.setCursor(7, 0);
    lcd.print(count);
    lcd.setCursor(0, 1);
    lcd.print("SAFE    ");

    if (lastButtonState == HIGH && buttonState == LOW) {
      count++;
      Serial.println("Pneumatic Activated");

      digitalWrite(solenoidPin, HIGH);   
      delay(500);                        
      digitalWrite(solenoidPin, LOW);    
    }
  }

  lastButtonState = buttonState;
}
