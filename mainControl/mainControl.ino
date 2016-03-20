#include <avr/pgmspace.h>
#include <stdio.h>
#include <Servo.h>;

//Trigger button
int FIRE = 0;
const int button = 2;
const int buttonPower = 3;
const int laser = 1;

//lights and counter
const int led5 = 4;
const int led10 = 5;
const int led20 = 6;
const int led30 = 7;
const int led40 = 9;
boolean released = true;

const int distButton = 13;
int distCounter = 0;

//Servo values
Servo servox;
Servo servoy;
Servo trigger;

const int VRxPin = 0; //VRx pin connected to arduino pin A0
const int VRyPin = 1; //VRy pin connected to arduino in A1
const int SwButtonPin = 8; //SW pin connected to arduino pin D8

const int servoxPin = 11;
const int servoyPin = 12;
const int servozPin = 10;

int posx = 95;
int posy = 100;
int posz = 20;
boolean moveLeft = false;
boolean moveRight = false;
boolean moveUp = false;
boolean moveDown = false;

boolean userControl = true; //wack integer boolean flag
boolean increasing = true; //current direction of the servo in sweep mode

int pressed = -1; //this variable will determine whether joystick has been pressed down (selected)
int x = -1; //this variable will hold the X-coordinate value
int y = -1; //this variable will hold the Y-coordinate value


//Servo Functions
void readJoystick() {
  pressed = digitalRead(SwButtonPin); //reads whether joystick has been pressed down (selected) or not
  x = analogRead(VRxPin);//reads the X-coordinate value
  y = analogRead(VRyPin);//reads the Y-coordinate value
}

void sweepStep(int upperLimit, int lowerLimit, int servoSpeed) {
  if (increasing) {
    servox.write(servox.read() + servoSpeed);
    if (servox.read() >= upperLimit) {
      increasing = false;
    }
  }
  else {
    servox.write(servox.read() - servoSpeed);
    if (servox.read() <= lowerLimit) {
      increasing = true;
    }
  }
}
void controlStep(int motorSpeed) {
  x = x / 100;
  y = y / 100;

  servox.write(posx);
  servoy.write(posy);

  if (x >= 0 && x < 5) {
    moveLeft = true;
    moveRight = false;
  }
  if (y >= 0 && y < 5) {
  moveUp = true;
  moveDown = false;
  }

  if (x <= 10 && x > 5) {
    moveLeft = false;
    moveRight = true;
  }

  if (y <= 10 && y > 5) {
    moveUp = false;
    moveDown = true;
  }

  if (x == 5) {
    moveLeft = false;
    moveRight = false;
  }
  if (y == 5) {
    moveUp = false;
    moveDown = false;
  }

  if (moveLeft && posx < 135)
  {
    posx = posx + motorSpeed;
  }
  else if (moveRight && posx > 50)
  {
    posx = posx - motorSpeed;
  }
  if (moveUp && posy < 135)
  {
    posy = posy + motorSpeed;
  }
  else if (moveDown && posy > 50)
  {
    posy = posy - motorSpeed;
  }
}

void servoMovement(int controlSpeed, int sweepSpeed, int sweepUpperLimit, int sweepLowerLimit, int stepDelay){
  readJoystick();//calls this function which reads the digital input button SW, the X-coordinate and the Y-coordinate

  if (pressed == 0) {
    userControl = !userControl;
  }

  if (userControl == true) {
    controlStep(controlSpeed);
  }

  else if (userControl == false) {
    sweepStep(sweepUpperLimit, sweepLowerLimit, sweepSpeed);
  }
  delay(stepDelay);
}

void pullTrigger(){
  trigger.write(90);
  delay(300);
  trigger.write(20);
  delay(300);
}

int getAngle(float distance){
  float angle = 0.7*distance +96;
  return (int) angle;
}

void setLights(){
  digitalWrite(led5,LOW);
  digitalWrite(led10,LOW);
  digitalWrite(led20,LOW);
  digitalWrite(led30,LOW);
  digitalWrite(led40,LOW);
  int distCounterCopy = distCounter;
  if(distCounterCopy >= 40){
    distCounterCopy -= 40;
    digitalWrite(led40,HIGH);
  }
  if(distCounterCopy >= 30){
    distCounterCopy -= 30;
    digitalWrite(led30,HIGH);
  }
  if(distCounterCopy >= 20){
    distCounterCopy -= 20;
    digitalWrite(led20,HIGH);
  }
  if(distCounterCopy >= 10){
    distCounterCopy -= 10;
    digitalWrite(led10,HIGH);
  }
  if(distCounterCopy >= 5){
    distCounterCopy -= 5;
    digitalWrite(led5,HIGH);
  }
}

void setup() {
  //Trigger setup
  pinMode(button,INPUT);
  pinMode(buttonPower,OUTPUT);
  pinMode(laser,OUTPUT);
  //Lights and Counter set up
  pinMode(led5, OUTPUT);
  pinMode(led10, OUTPUT);
  pinMode(led20, OUTPUT);
  pinMode(led30, OUTPUT);
  pinMode(led40, OUTPUT);
  pinMode(distButton ,INPUT);
  Serial.begin(9600);
  //servo setup
  servox.attach(servoxPin);
  servox.write(posx); 
  servoy.attach(servoyPin);
  servox.write(posy);
  trigger.attach(servozPin);
  trigger.write(posz);
  pinMode(SwButtonPin, INPUT);//sets the SW switch as input
  digitalWrite(SwButtonPin, HIGH);//sets the SW button HIGH
  Serial.begin(9600);//sets the baud rate
}

void loop() {
  digitalWrite(buttonPower,HIGH);
  digitalWrite(laser,HIGH);
  FIRE = digitalRead(button);
  if(FIRE == LOW){
    if(distCounter != 0){
        servox.write(95);
        delay(500);
        servoy.write(115);
        delay(500);
        posy = getAngle(distCounter);
        servoy.write(posy);
        delay(2000);
    }
    pullTrigger();
  }
  if(digitalRead(distButton)==LOW && released == true){
    if(distCounter <= 55){
      distCounter += 5;
    }
    else{
      distCounter = 0;
    }
    while (digitalRead(distButton)==LOW)
    {
      released = false;
    }
    released = true;
  }
  setLights();
  servoMovement(1, 1, 180, 0, 15);

}
