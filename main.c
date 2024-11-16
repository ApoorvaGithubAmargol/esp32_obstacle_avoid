#include <ESP32Servo.h>

//obstacle avoidance code by apoorva

Servo myservo;
int pos=90;

const int trigpin=2; //ultrasonic
const int echopin=4;
long duration;
long distance;

int motor1Pin1=18; //motor
int motor1Pin2=19;
int motor2Pin1=26;
int motor2Pin2=27;

float measuredistance() {
digitalWrite(trigpin,LOW);
delayMicroseconds(2);
digitalWrite(trigpin,HIGH);
delayMicroseconds(10);
digitalWrite(trigpin,LOW);
duration=pulseIn(echopin,HIGH);
distance= duration*0.034/2;
delay(100);
return distance;
}

void angleleft()
{
for(pos=90;pos<=180;pos+=1){
  myservo.write(pos);
  delay(20);
}
}

void angleright()
{
for(pos=90;pos>=0;pos-=1){
  myservo.write(pos);
  delay(20);
}
}

void anglebackright()
{
  for(pos=0;pos<=90;pos+=1){
  myservo.write(pos);
  delay(20);
  }
}

void anglebackleft()
{
  for(pos=180;pos>=90;pos-=1){
  myservo.write(pos);
  delay(20);
  }
}

void front()
{
  digitalWrite(motor1Pin1,HIGH);
  digitalWrite(motor1Pin2,LOW);
  digitalWrite(motor2Pin1,HIGH);
  digitalWrite(motor2Pin2,LOW);
    }

void stopmotor()
{
    digitalWrite(motor1Pin1,LOW);
    digitalWrite(motor1Pin2,LOW);
    digitalWrite(motor2Pin1,LOW);
    digitalWrite(motor2Pin2,LOW);
}

    
void setup() {
  Serial.begin(9600);   //ultra sonic
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(motor1Pin1,OUTPUT);   //motor
  pinMode(motor1Pin2,OUTPUT);
  pinMode(motor2Pin1,OUTPUT);
  pinMode(motor2Pin2,OUTPUT);
  digitalWrite(motor1Pin1,LOW);
  digitalWrite(motor1Pin2,LOW);
  digitalWrite(motor2Pin1,LOW);
  digitalWrite(motor2Pin2,LOW);
  myservo.attach(25);   //servo
}

void loop() {
  float f=0;
  float r= 0;
  float l= 0;
  f=measuredistance();

if(f>20){     // for distance greater than 20
  front();
}

else if(f<20){   //for distance less than 20
  stopmotor();
  delay(500);
  
  angleright();
  delay(1000);
  float r= measuredistance();
  Serial.println("right check"+String(r));
  
  anglebackright();
  delay(1000);
  
  angleleft();
  Serial.println("left check"+String(l));
  
  measuredistance();
  float l= measuredistance();
  anglebackleft();
  delay(1000);

  if (r>l && r>20){
    Serial.println("move right");
    digitalWrite(motor1Pin1,HIGH);
    digitalWrite(motor1Pin2,LOW);
    digitalWrite(motor2Pin1,LOW);
    digitalWrite(motor2Pin2,HIGH);
    delay(500);
    stopmotor();
    delay(100);
    front();
  }
  
  else if (l>r && l>20){
    Serial.println("move left");
    digitalWrite(motor1Pin1,LOW);
    digitalWrite(motor1Pin2,HIGH);
    digitalWrite(motor2Pin1,HIGH);
    digitalWrite(motor2Pin2,LOW);
    delay(500);
    stopmotor();
    delay(100);
    front();
  }

  else{
    Serial.println("no path");
    stopmotor();
  }
  
}//end for f<20

delay(1000);
}

//end
