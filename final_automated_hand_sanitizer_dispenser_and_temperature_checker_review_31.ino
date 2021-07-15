// defines pins numbers
const int servo = 9;
const int trigPin = 10;
const int echoPin = 11;

// defines variables
long duration;
int distance;

#include <Servo.h>
#include<LiquidCrystal.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
LiquidCrystal lcd(2,3,4,5,6,7);
int tempin=A0;
double temp=0;
int pos = 0;    // variable to store the servo position
int buzzpin=12;
int dcmotor=13;
void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  myservo.attach(servo);  // attaches the servo on pin 9 to the servo object  
  myservo.write(0);   // Sets Servo to initially 0 degrees 
  Serial.begin(9600); // Starts the serial communication
  lcd.begin(16,2);
  pinMode(tempin,INPUT);
  pinMode(buzzpin,OUTPUT);
  pinMode(dcmotor,OUTPUT);
}

void loop() 
{
    lcd.print("Hand Sanitizer");
    lcd.setCursor(0,1);
    lcd.print("Insert Hand");
    delay(500);
    lcd.clear();
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
    //Servo
    if(distance<10 || distance>300)
    { //Check distance is less than 10cm
      temp=tempread();
      lcd.print("Hand Detected");
      if(temp>=38)
      {
        tone(buzzpin, 220, 500);
        myservo.write(45); // Sets Servo in stages from 0 to 180 degrees so soap does not pitch out. 
       delay(100);
       myservo.write(90);
       delay(1000);
       //myservo.write(135);
       //delay(100);
       //myservo.write(180); //Ajust how far you want the servo to go.
       //delay(1000);
       myservo.write(0); // Reset the servo to 0 Degrees
       delay(3000);   //Delay the next time someone can get soap
      }
      lcd.setCursor(0,1);
      lcd.print("Temp: ");
      lcd.print(temp);
      digitalWrite(dcmotor,HIGH);
      delay(1000);
      digitalWrite(dcmotor,LOW);
      delay(3000);
    }
  lcd.clear();
}
double tempread()
{
  temp=analogRead(tempin);
  temp=temp*0.4878-49.6325;
  return temp;
}