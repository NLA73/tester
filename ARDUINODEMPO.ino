#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
const int trigPin = 10;
const int echoPin = 11;
const int LED_RED = 5;
const int LED_YELLOW = 6;
const int LED_GREEN = 7;
const int Buzzer_Pin = 8;
const int closeDistance = 10;
const int medDistance = 20;
const int farDistance = 50;
const long MAX_DISTANCE = 250L;
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (LED_RED, OUTPUT);
  pinMode (LED_YELLOW, OUTPUT);
  pinMode (LED_GREEN, OUTPUT);
  Serial.begin(115200);
  lcd.backlight();
  lcd.init();
}

void loop() {
  function1();
  function2();
  displayDistance();
  delay(200);
}

void function1(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds (2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if(distance >= MAX_DISTANCE){
    distance = 0;
  }
  Serial.print("Distance: ");
  Serial.println(distance);
}

void function2(){
  turnLightsOff();
  if(distance >= farDistance){
    noTone(Buzzer_Pin);
  } else if(distance <= farDistance && distance >= medDistance){
    digitalWrite(LED_RED, HIGH);
    tone(Buzzer_Pin, 500);
    delay(450);
    noTone(Buzzer_Pin);
    delay(500);
  } else if(distance <= medDistance && distance >= closeDistance){
    digitalWrite(LED_YELLOW, HIGH);
    tone(Buzzer_Pin, 500);
    delay(200);
    noTone(Buzzer_Pin);
    delay(70);
  } else if(distance <= closeDistance && distance >= 1){
    digitalWrite(LED_GREEN, HIGH);
    tone(Buzzer_Pin, 500);
  }
}

void turnLightsOff(){
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void displayDistance(){
  lcd.setCursor(0,0);
  lcd.print("ALARM JARAK");
  lcd.setCursor(0,1);
  lcd.print("JARAK =  ");
  lcd.setCursor(8,1);
  lcd.print(distance);
  lcd.setCursor(11,1);
  lcd.print(" Cm");
}