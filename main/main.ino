#include <ESP32Servo.h>

Servo myServo;
const int servoPin = 18; // Servo Signal Pin
const int ledPin = 2;   // Onboard LED Pin

//pulse width, a random pulse width will be chosen between these two numbers
//this is the lowest and highest servo position
int minPulse = 800; // Minimum pulse width (microseconds)
int maxPulse = 1300; // Maximum pulse width (microseconds)

//wait time between moves, a random time will be chosen between these two numbers
int minWait = 8000;  // Minimum wait time (milliseconds)
int maxWait = 25000; // Maximum wait time (milliseconds)

int moveDuration = 1000; // Time taken for each move (milliseconds)

//initial position
int currentPos = (minPulse + maxPulse) / 2; // Start at midpoint

void setup() {
  Serial.begin(115200);
  
  // Standard setup for ESP32 PWM
  ESP32PWM::allocateTimer(0);
  myServo.setPeriodHertz(50); 
  myServo.attach(servoPin, 500, 2400); 
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

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
    
    // Rapid blink: Toggle LED every 50ms
    digitalWrite(ledPin, (millis() / 50) % 2);

    Serial.println(currentStep); // Output for Plotter
    delay(15); 
  }
  myServo.writeMicroseconds(end); 
  digitalWrite(ledPin, LOW); // Ensure LED is off after move
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
