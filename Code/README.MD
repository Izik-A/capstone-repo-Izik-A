The code used for both the button and pneumatic system were both made in In Arduino's coding language, C++. The following codes are listed below and will be added upon as more developments in the project occur.

# Button Sensor

const int buttonPin = A0;      // Pin connected to NO
int buttonState = HIGH;        // Current reading of the button
int lastButtonState = HIGH;    // Previous reading of the button

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Detect press: LOW now, HIGH before
  if (lastButtonState == HIGH && buttonState == LOW) {
    Serial.println("Button Pressed"); // Trigger once
  }

  lastButtonState = buttonState; // Save state for next loop
}

# Pneumatic System

void setup() {

  pinMode(7, OUTPUT);
}

void loop() {
  digitalWrite(7, HIGH);   
  delay(1000);                       
  digitalWrite(7, LOW);    
  delay(1000);                       
}



# Combined Code (pneumatic works when button is pressed)

const int buttonPin = A0;      // Button on A0
const int solenoidPin = 7;     // Solenoid valve control pin

int buttonState = HIGH;
int lastButtonState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Button with internal pull-up
  pinMode(solenoidPin, OUTPUT);      // Solenoid output
  digitalWrite(solenoidPin, LOW);    // Make sure it's OFF
  Serial.begin(9600);
}

void loop() {

  buttonState = digitalRead(buttonPin);

  // Detect button press (HIGH → LOW)
  if (lastButtonState == HIGH && buttonState == LOW) {

    Serial.println("Pneumatic Activated");

    digitalWrite(solenoidPin, HIGH);   // Turn ON pneumatic valve
    delay(500);                       // Keep ON for 1 second
    digitalWrite(solenoidPin, LOW);    // Turn OFF
  }

  lastButtonState = buttonState;
}
