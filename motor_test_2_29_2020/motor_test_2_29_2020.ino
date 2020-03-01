// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4;
const int LEDPIN = 13;
const int SENSORPIN = 5; 
int sensorState = 0;
unsigned long previousTime;
// CAN CHANGE ITS VALUE BASED ON THE TIME OF PLATFORM RISING AND FALLING
const long interval = 3000;
unsigned long currentTime;


void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  // initialize the LED pin as an output:
  pinMode(LEDPIN, OUTPUT);      
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN, INPUT);
  // turn on the pullup 
  digitalWrite(SENSORPIN, HIGH);
  //initialize the timer
  previousTime = 0;
  Serial.begin(9600);
}


void turn() {
  // CAN CHANGE ITS VALUE BASED ON ITS DIRECTION OF ROTATING (HIGH - CCW, LOW - CW)
  digitalWrite(dirPin,HIGH);
  currentTime = millis();
  previousTime = currentTime;
  while (currentTime - previousTime <= interval){
    currentTime = millis();
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500);
  }
  // CAN CHANGE ITS VALUE BASED ON ITS UNLOADING TIME (may add more function)
  delay(1000);
  // CAN CHANGE ITS VALUE BASED ON ITS DIRECTION OF ROTATING (HIGH - CCW, LOW - CW)
  digitalWrite(dirPin,LOW);
  currentTime = millis();
  previousTime = currentTime;
  while (currentTime - previousTime <= interval) {
    currentTime = millis();
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500);
  }
}


void loop() {
  // read the state of the pushbutton value:
  sensorState = digitalRead(SENSORPIN);
  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  if (sensorState == LOW){
    digitalWrite(LEDPIN, HIGH);
    turn();
  }
  else {
    digitalWrite(LEDPIN, LOW);
  }
}
