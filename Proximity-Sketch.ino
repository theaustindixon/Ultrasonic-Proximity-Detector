//Ultrasonic Proximity Detector
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
int voltpin = 9;     // VCC for Ultrasonic Sensor HC-SR04
int voltpin2 = 6;    // VCC for LCD
long duration, inches; // variables for Sensor Math
int pos = 0;    // variable to store the servo position


LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  myservo.attach(7);  // attaches the servo on pin 7 to the servo object
  myservo.writeMicroseconds(1500);
  
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH); // 5v out to sensor

  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH); // 5v out to servo

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   
  lcd.init();           // initialize the lcd 
  lcd.backlight();
  
  Serial.begin(9600); //Starts the serial connection
  
}


void loop()
{
  //////////////////////////////////////////////////////////////////////////////
  // now lets get that servo moving and output to LCD
  
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree


    //******************************************************************************
    // Sensor Math
    
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
     
    // Convert the time into a distance
    duration = pulseIn(echoPin, HIGH); // duration is the time (in microseconds) from the sending of the ping to the reception of its echo off of an object
    inches = (duration/2) / 74;        // divide by 74 or multiply by 0.0135
    inches = round(inches);            // round the number cause the lcd does weird things otherwise 
 
    //******************************************************************************

    if (inches < 12) { // sensor detects obect within 12 inches
      
      // Print a message to the LCD.
      delay(15);
      lcd.clear();
      lcd.setCursor(0,0); // left, top
      lcd.print("Inches: ");
      lcd.print(inches);
      lcd.setCursor(0,1); // left, bottom
      lcd.print("OBJECT TOO CLOSE");
      
      pos = pos - 1; // basically, servo doesn't move until object is further than 12 inches away

    }
    else {
      
      // Print a message to the LCD.
      delay(15);
      lcd.clear();
      lcd.setCursor(0,0); // left, top
      lcd.print("Inches: ");
      lcd.print(inches);
        
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees

    //******************************************************************************
    // Sensor Math

    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
      
    // Convert the time into a distance
    duration = pulseIn(echoPin, HIGH); // duration is the time (in microseconds) from the sending of the ping to the reception of its echo off of an object
    inches = (duration/2) / 74;        // divide by 74 or multiply by 0.0135
    inches = round(inches);            // round the number cause the lcd does weird things otherwise 

    //******************************************************************************
    
    if (inches < 12) { // sensor detects obect within 12 inches
      
      // Print a message to the LCD.
      delay(15);
      lcd.clear();
      lcd.setCursor(0,0); // left, top
      lcd.print("Inches: ");
      lcd.print(inches);
      lcd.setCursor(0,1); // left, bottom
      lcd.print("OBJECT TOO CLOSE");
      
      pos = pos - 1; // basically, servo doesn't move until object is further than 12 inches away

    }
    else {
      
      // Print a message to the LCD.
      delay(15);
      lcd.clear();
      lcd.setCursor(0,0); // left, top
      lcd.print("Inches: ");
      lcd.print(inches);
      
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

    
  }

  //////////////////////////////////////////////////////////////////////////////

}
