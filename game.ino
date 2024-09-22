#define D2 2

const int rotationPin = D2;
int buttonState;
int lastButtonState;
const unsigned long timeWindow = 5 * 1000; 

const int maxPresses = 256;
unsigned long rotationTimes[maxPresses]; 
int pressIndex = 0; 

void setup() {
  pinMode(rotationPin, INPUT_PULLUP); 
  Serial.begin(9600); 
  lastButtonState = digitalRead(rotationPin);
}

void loop() {
  int currentState = digitalRead(rotationPin);

  if (currentState != buttonState) {
    buttonState = currentState;
    if (buttonState == LOW) {
      rotationTimes[pressIndex] = millis(); 
      pressIndex = (pressIndex + 1) % maxPresses; 
    }
  }

  unsigned long currentTime = millis();
  int validPressCount = 0; 
  for (int i = 0; i < maxPresses; i++) {
    if ((currentTime - rotationTimes[i]) <= timeWindow) {
      validPressCount++;
    }
  }
  Serial.println(validPressCount);
  lastButtonState = currentState;
  delay(100);  
}
