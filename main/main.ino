#include <ESP32Servo.h>

Servo myServo;
const int servoPin = 18; // Connect to pin labeled D18 on your NodeMCU

int minPulse = 1000; // Minimum pulse width (microseconds)
int maxPulse = 1800; // Maximum pulse width (microseconds)

int minWait = 8000;  // Minimum wait time (milliseconds)
int maxWait = 25000; // Maximum wait time (milliseconds)

int moveDuration = 2000; // Time taken for each move (milliseconds)

int currentPos = (minPulse + maxPulse) / 2; // Start at midpoint

void setup() {
  Serial.begin(115200);
  
  // Standard setup for ESP32 PWM
  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50); 
  myServo.attach(servoPin, 500, 2400); 
  
  myServo.writeMicroseconds(currentPos); // Start at midpoint
  Serial.println("System Ready. Starting in 5 seconds...");
  delay(5000);
}

// Easing function: Smoothly moves from A to B (microseconds)
// Outputs values for Serial Plotter compatibility
void moveWithEasing(int start, int end) {
  float duration = (float)moveDuration; 
  unsigned long startMillis = millis();
  
  while (millis() - startMillis < duration) {
    float t = (millis() - startMillis) / duration;
    
    // Smoothstep Ease-In/Out formula: 3t^2 - 2t^3
    float easedT = t * t * (3 - 2 * t);
    
    int currentStep = start + (end - start) * easedT;
    myServo.writeMicroseconds(currentStep);
    Serial.println(currentStep); // Output for Plotter
    delay(15); 
  }
  myServo.writeMicroseconds(end); 
  Serial.println(end); 
}

void loop() {
  // Always choose a random target between min and max
  int targetPos = random(minPulse, maxPulse + 1); 

  moveWithEasing(currentPos, targetPos);
  currentPos = targetPos;

  // Random wait between minWait and maxWait
  long waitTime = random(minWait, maxWait + 1); 
  delay(waitTime);
}
