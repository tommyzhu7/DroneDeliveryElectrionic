#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

// PIN DEFINITIONS
const int stepPin1 = 3; // motor pins 1
const int dirPin1 = 4;
const int stepPin2 = 5; // motor pins 2
const int dirPin2 = 6;
const int LEDPIN = 13;
const int SENSORPIN = 7; // ir sensor pin

int sensorState = 0, lastState=0;         // variable for reading the pushbutton status

float x;
float y;
float z;

unsigned long previousTime;
const long interval = 4500;
unsigned long currentTime;

void setup() {
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  // initialize the LED pin as an output:
  pinMode(LEDPIN, OUTPUT);      
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN, INPUT);     
  digitalWrite(SENSORPIN, HIGH); // turn on the pullup
  
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

// turing motor clockwise
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

// tile the platform one side to load off packages
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

void gyro_setup(void)
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
}

// gyro working code
void gyro_work(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  
  /* Display the floating point data */
  x = event.orientation.x;
  y = event.orientation.y;
  z = event.orientation.z;
  
  delay(100);
}

// stabilize the platform
// location and axis should be tested later
void stabilize() {
  gyro_work();
  while (x > 2) { // suppose the x-axis is the axis that can be changed
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
    gyro_work();
  }
  while (x < -2) {
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
    gyro_work();
  }
}

void loop() {
  while (SENSORPIN == LOW){
    CCW();
    stabilize();
    sensorState = digitalRead(SensorPin);
  }
  // time is changed by delayMicroseconds function in CCW()
  tilt();
  delayMicroSeconds(1000);
  while (SENSORPIN == LOW){
    CW;
    stabilize();
    sensorState = digitalRead(SensorPin);
  }
}
