// PIN DEFINITIONS
const int stepPin1 = 3;
const int dirPin1 = 4;
const int stepPin2 = 5;
const int dirPin2 = 6;
unsigned long previousTime;
const long interval = 4500;
unsigned long currentTime;

void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  
  previousTime = 0;
  Serial.begin(9600);
}

// Controlling motor direction with dirPin: HIGH - CCW; LOW - CW
void CCW() {
  digitalWrite(dirPin1, HIGH);
  digitalWrite(dirPin2, HIGH);
  currentTime = millis();
  previousTime = currentTime;
  while (currentTime - previousTime <= interval) {
    currentTime = millis();
    digitalWrite(stepPin1, HIGH);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
}

void CW() {
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, LOW);
  currentTime = millis();
  previousTime = currentTime;
  while (currentTime - previousTime <= interval) {
    currentTime = millis();
    digitalWrite(stepPin1, HIGH);
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
}

void tilt() {
  digitalWrite(dirPin1, LOW);
  currentTime = millis();
  previousTime = currentTime();
  while (currentTime - previousTime <= interval/2) {
    currentTime = millis();
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
   }
}

void stabilize() {
  digitalWrite(dirPin1, HIGH);
  currentTime = millis();
  previousTime = currentTime();
  while (currentTime - previousTime <= interval/2) {
    currentTime = millis();
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
   }
}

void loop() {
  CW();
  CCW();
  tilt();
  delayMicroSeconds(1000);
  stabilize();
  break;
 }
