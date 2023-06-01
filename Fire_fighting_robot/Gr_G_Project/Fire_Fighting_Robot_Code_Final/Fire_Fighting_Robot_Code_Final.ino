#include <Servo.h>
Servo myservo;

 
/*-------defining Inputs------*/
int Left_S = A0;         // left sensor
int Right_S = A1;      // right sensor
int Forward_S = A2;    //forward sensor
int Smoke_S = A3;    //smoke sensor

int pos = 0;
 
/*-------defining Outputs------*/
int LM1 = 2;       // left motor
int LM2 = 3;      // left motor
int RM1 = 4;     // right motor
int RM2 = 5;    // right motor
int pump = 6;
int Buzzer = 7;
 
void setup()
{
  pinMode(Left_S, INPUT);
  pinMode(Right_S, INPUT);
  pinMode(Forward_S, INPUT);
  pinMode(Smoke_S, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(Buzzer, OUTPUT);


  Serial.begin(9600);
  myservo.attach(11); 
}
 
void put_off_fire()
{
    delay (500);
 
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    
   digitalWrite(pump, HIGH); delay(500);
    
    for (pos = 50; pos <= 130; pos += 1) { 
    myservo.write(pos); 
    delay(10);  
  }
  for (pos = 130; pos >= 50; pos -= 1) { 
    myservo.write(pos); 
    delay(10);
  }
  
 delay(100);
 digitalWrite(pump, LOW);
 
}
 
void loop()
{

  int flameval1 = digitalRead (Left_S) ;
  int flameval2 = digitalRead (Right_S) ;
  int flameval3 = digitalRead (Forward_S) ;
  int smokeval = digitalRead(Smoke_S);
  Serial.print("Left_Flame_Value = ");
  Serial.println(flameval1);
  Serial.print("Right_Flame_Value = ");
  Serial.println(flameval2);
  Serial.print("Forward_Flame_Value = ");
  Serial.println(flameval3);
  Serial.print("Smoke_Value = ");
  Serial.println(smokeval);
    
 
    if (flameval1 == LOW and flameval2 == LOW and flameval3 == LOW and smokeval == LOW) //If Fire OR Smoke not detected all sensors are zero
    {
    //Do not move the robot

    Serial.println(" |...SAFE ENVIRONMENT...| ");
    
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    digitalWrite(Buzzer, LOW);
    }
    
    else if (flameval1 == HIGH or smokeval == HIGH) //If Fire OR Smoke is straight ahead
    {
    //Move the robot forward

    Serial.println(" |...DANGER ENVIRONMENT: WARNING!...| ");
    
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    digitalWrite(Buzzer, HIGH);

    put_off_fire();
    
    }
    
    else if (flameval2 == HIGH or smokeval == HIGH) //If Fire OR Smoke is to the left
    {
    //Move the robot left

    Serial.println(" |...DANGER ENVIRONMENT: WARNING!...| ");
    
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    digitalWrite(Buzzer, HIGH);

    put_off_fire();
    
    }
    
    else if (flameval3 == HIGH or smokeval == HIGH) //If Fire OR Smoke is to the right
    {
    //Move the robot right

    Serial.println(" |...DANGER ENVIRONMENT: WARNING!...| ");
    
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    digitalWrite(Buzzer, HIGH);

    put_off_fire();
    
    }
    
delay(300); //Slow down the speed of robot
 

}
