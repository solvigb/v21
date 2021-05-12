//www.elegoo.com

#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

#define Echo 12 
int Trig = A3;
int hljod = A0;
int ljos1 = A1;
int ljos2 = A2; 

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define carSpeed 120
#define aframmhradi 100
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

void forward(){ 
  analogWrite(ENA, aframmhradi);
  analogWrite(ENB, aframmhradi);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(ljos1, LOW);
  digitalWrite(ljos2, LOW);
  Serial.println("Forward");
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(ljos1, LOW);
  digitalWrite(ljos2, LOW);
  Serial.println("Back");
}

void left() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  digitalWrite(ljos2, HIGH);
  digitalWrite(ljos2, LOW);
  digitalWrite(ljos2, HIGH);
  Serial.println("Left");
}

void right() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(ljos1, HIGH);
  Serial.println("Right");
}

void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  tone(hljod, 200);
  Serial.println("Stop!");
  noTone(hljod);
} 

//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 78 ;       
  return (int)Fdistance;
}  

void setup() { 
  myservo.attach(3);  // attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(hljod, OUTPUT);
  pinMode(ljos1, OUTPUT);
  pinMode(ljos2, OUTPUT);
  
  stop();
} 

void loop() { 
    myservo.write(90);  //setservo position according to scaled value
    delay(250); 
    middleDistance = Distance_test();

    if(middleDistance <= 20) {     
      stop();
      delay(250);                         
      myservo.write(10);          
      delay(500);      
      rightDistance = Distance_test();
      
      delay(500);
      myservo.write(100);              
      delay(1000);                                                  
      myservo.write(190);              
      delay(1000); 
      leftDistance = Distance_test();
      
      delay(500);
      myservo.write(90);              
      delay(1000);
      if(rightDistance > leftDistance) {
        right();
        delay(360);
      }
      else if(rightDistance < leftDistance) {
        left();
        delay(360);
      }
      else if((rightDistance <= 10) || (leftDistance <= 10)) {
        back();
        delay(180);
      }
      else {
        forward();
      }
    }  
    else {
        forward();
    }                     
}
