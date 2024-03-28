#include <Servo.h>
Servo myservo;
long duration;
int distance;
const int trigPin = 12;
const int echoPin = 11;
int delay_value = 400;
int temp_distance;
#define AIN1 6
#define BIN1 9
#define AIN2 7
#define BIN2 8
#define PWMA 5
#define PWMB 10
#define STBY 2


void forward(){
digitalWrite(AIN1, HIGH);
digitalWrite(AIN2, LOW);
digitalWrite(BIN1, HIGH);
digitalWrite(BIN2, LOW);
analogWrite(PWMA, 255);
analogWrite(PWMB, 255);
}

void backward(){
digitalWrite(AIN2, HIGH);
digitalWrite(AIN1, LOW);
digitalWrite(BIN2, HIGH);
digitalWrite(BIN1, LOW);
analogWrite(PWMA, 255);
analogWrite(PWMB, 255);
}
void leftward(){
digitalWrite(AIN2, HIGH);
digitalWrite(AIN1, LOW);
digitalWrite(BIN1, HIGH);
digitalWrite(BIN2, LOW);
analogWrite(PWMA, 255);
analogWrite(PWMB, 255);
}

void rightward(){
digitalWrite(AIN1, HIGH);
digitalWrite(AIN2, LOW);
digitalWrite(BIN2, HIGH);
digitalWrite(BIN1, LOW);
analogWrite(PWMA, 255);
analogWrite(PWMB, 255);
}

void stopp(){
digitalWrite(AIN2, HIGH);
digitalWrite(AIN1, HIGH);
digitalWrite(BIN1, HIGH);
digitalWrite(BIN2, HIGH);
}

int getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void setup()
{
  pinMode(AIN1, OUTPUT);
pinMode(AIN2, OUTPUT);
pinMode(BIN1, OUTPUT);
pinMode(BIN2, OUTPUT);
pinMode(PWMA, OUTPUT);
pinMode(PWMB, OUTPUT);
pinMode(STBY, OUTPUT);
digitalWrite(STBY, HIGH);
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  myservo.attach(3);
  myservo.write(80);
  delay(100);
  Serial.begin(9600);
}


void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance < 20){
    Serial.println("OBJ DETECTED");
    backward();
    delay(50);
    stopp();
    myservo.write(180);
    delay(400);
    int leftDistance = getDistance();
    myservo.write(0);
    delay(700);
    int rightDistance = getDistance();
    myservo.write(80);
    delay(300);
    Serial.println("CHECKED DIS");
    if(leftDistance < rightDistance){
      Serial.println("RIGHT");
      temp_distance = getDistance();
      while(temp_distance < 30){
        Serial.println("TURNING R");
        rightward();
        delay(200);
        temp_distance = getDistance();
      }

      }
    
    else{
      Serial.println("LEFT");
      temp_distance = getDistance();
      while(temp_distance < 30){
        Serial.println("Turning left");
        leftward();
        delay(200);
        temp_distance = getDistance();
      }
    }
  }
  else{
    Serial.println("FORWARD");
    forward();
  }

}