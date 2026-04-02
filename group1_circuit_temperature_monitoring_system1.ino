#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int tempSensor = 0;

int potPin = 1;

int buzzerPin = 10;

int redPin = 9;
int bluePin = 8;
int greenPin = 7;




void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  
  int reading = analogRead(tempSensor);
  
  //base reading of the temperature sensor before conversion
  /*
  lcd.setCursor(0,0);
  lcd.print(reading);
  */
  
  float tempF = map(reading, 153, 1023, 50, 200);
  
  int potValue = analogRead(potPin);
  
  float potAdjust = map(potValue, 0, 1023, -20, 20);
  
  tempF = tempF + potAdjust;  
  
  lcd.setCursor(0,1);
  lcd.print("temperature: ");
  
  lcd.setCursor(13,1);
  lcd.print(tempF);
  
  if(tempF > 72){
  	digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
  }
  
  else if(tempF >= 67 and tempF <= 72){
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, HIGH);
  }
  
  else if(tempF < 67){
  	digitalWrite(redPin, LOW);
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, LOW);
  }
  
  if(tempF >= 80){
    lcd.setCursor(0,0);
    lcd.print("Too Hot");
  	tone(buzzerPin, 1000);  
  }else{
  	noTone(buzzerPin);
  }
  
}