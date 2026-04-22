The code used for both the button and pneumatic system were both made in In Arduino's coding language, C++. The following codes are listed below and will be added upon as more developments in the project occur.

# Button Sensor
```

const int buttonPin = A0;      

int buttonState = HIGH;       
int lastButtonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Detect press: LOW now, HIGH before
  if (lastButtonState == HIGH && buttonState == LOW) {
    Serial.println("Button Pressed"); 
  }

  lastButtonState = buttonState; 
}
```
# Pneumatic System
```
void setup() {

  pinMode(7, OUTPUT);
}

void loop() {
  digitalWrite(7, HIGH);   
  delay(1000);                       
  digitalWrite(7, LOW);    
  delay(1000);                       
} 

```

# Combined Code (pneumatic works when button is pressed)
```
const int buttonPin = A0;
const int solenoidPin = 7;

int buttonState = HIGH;
int lastButtonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(solenoidPin, OUTPUT);     
  digitalWrite(solenoidPin, LOW);    
  Serial.begin(9600);
}

void loop() {

  buttonState = digitalRead(buttonPin);

  // Detect button press (HIGH → LOW)
  if (lastButtonState == HIGH && buttonState == LOW) {

    Serial.println("Pneumatic Activated");

    digitalWrite(solenoidPin, HIGH);
    delay(500);     
    digitalWrite(solenoidPin, LOW);
  }

  lastButtonState = buttonState;
}
```


# Full system with a safety

```
#include <LiquidCrystal.h>

const int buttonPin = A0;      
const int solenoidPin = 7;     
const int pirPin = 2;
int count = 0;                 

int buttonState = HIGH;
int lastButtonState = HIGH;
int motionDetected = LOW;


LiquidCrystal lcd(11, 12, 5, 6, 3, 4);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(solenoidPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(solenoidPin, LOW);
  
  lcd.begin(8, 2); 
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("SYSTEM");
  lcd.setCursor(0, 1);
  lcd.print("READY");
  delay(2000);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  motionDetected = digitalRead(pirPin);


  if (motionDetected == HIGH) {
    digitalWrite(solenoidPin, LOW); 
    lcd.setCursor(0, 0);
    lcd.print("WARNING ");
    lcd.setCursor(0, 1);
    lcd.print("MOTION! ");
    delay(500);
  } 
  else {
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
```
