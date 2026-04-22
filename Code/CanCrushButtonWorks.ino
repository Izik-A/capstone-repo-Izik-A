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