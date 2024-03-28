#include <Servo.h>

// Define the servo object for controlling the robot's direction
Servo myservo;

// Variables to store the duration of the echo pulse and calculate distance
long duration;
int distance;

// Pin definitions for the ultrasonic sensor
const int trigPin = 12;
const int echoPin = 11;

// Define motor control pins
#define AIN1 6
#define BIN1 9
#define AIN2 7
#define BIN2 8
#define PWMA 5 // PWM control for motor A
#define PWMB 10 // PWM control for motor B
#define STBY 2 // Standby

// Function to move the robot forward
void forward(){
  // Setting motor directions for forward movement
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  // Applying full speed
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);
}

// Function to move the robot backward
void backward(){
  // Setting motor directions for backward movement
  digitalWrite(AIN2, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN2, HIGH);
  digitalWrite(BIN1, LOW);
  // Applying full speed
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);
}

// Function to turn the robot left
void leftward(){
  // Setting motor directions for leftward movement
  digitalWrite(AIN2, HIGH);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  // Applying full speed
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);
}

// Function to turn the robot right
void rightward(){
  // Setting motor directions for rightward movement
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, HIGH);
  digitalWrite(BIN1, LOW);
  // Applying full speed
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);
}

// Function to stop the robot
void stopp(){
  // Applying high to all control pins to stop motors
  digitalWrite(AIN2, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, HIGH);
}

// Function to calculate and return the distance to an object in front of the ultrasonic sensor
int getDistance(){
  // Triggering the ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

// Setup function, runs once when you press reset or power the board
void setup()
{
  // Initialize motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH); // Disable standby
  
  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  // Attach the servo on pin 3 to the servo object
  myservo.attach(3);
  myservo.write(80); // Initialize servo to 80 degrees
  delay(100); // Short delay to let servo reach position
  
  // Start serial communication
  Serial.begin(9600);
}

// Main loop function, runs over and over again forever
void loop()
{
  // Check for obstacles and navigate accordingly
  if (getDistance() < 20){
    Serial.println("OBJ DETECTED"); // Object detected within 20 cm
    backward(); // Move backward briefly
    delay(50);
    stopp(); // Stop movement

    // Check distances to the left and right
    myservo.write(180); // Look right
    delay(400);
    int leftDistance = getDistance(); // Measure distance to the left
    myservo.write(0); // Look left
    delay(700);
    int rightDistance = getDistance(); // Measure distance to the right
    myservo.write(80); // Return to center
    delay(300);
    
    // Navigate based on distances
    if(leftDistance < rightDistance){
      Serial.println("RIGHT"); // Right side is clearer
      // Turn right until path is clear
      while(getDistance() < 30){
        Serial.println("TURNING R");
        rightward();
        delay(200);
      }
    }  
    else{
      Serial.println("LEFT"); // Left side is clearer
      // Turn left until path is clear
      while(getDistance() < 30){
        Serial.println("Turning left");
        leftward();
        delay(200);
      }
    }
  }
  else{
    Serial.println("FORWARD"); // Path is clear, move forward
    forward();
  }
}
