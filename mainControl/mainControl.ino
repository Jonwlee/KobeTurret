/*
* Nerfturret
* profhacks
* 3/12/16
*/
#include <avr/pgmspace.h>

#include <Servo.h>;

Servo servox;
Servo servoy;

const int VRxPin = 0; //VRx pin connected to arduino pin A0
const int VRyPin = 1; //VRy pin connected to arduino in A1
const int SwButtonPin = 8; //SW pin connected to arduino pin D8
const char Up = 2;
const char Down = 3;
const char Left = 4;
const char Right = 5;

int posx = 90;
int posy = 90;
boolean moveLeft = false;
boolean moveRight = false;
boolean moveUp = false;
boolean moveDown = false;

boolean userControl = true; //wack integer boolean flag
boolean increasing = true; //current direction of the servo in sweep mode

int pressed = -1; //this variable will determine whether joystick has been pressed down (selected)
int x = -1; //this variable will hold the X-coordinate value
int y = -1; //this variable will hold the Y-coordinate value
int motorSpeed;

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
    digitalWrite(Left, HIGH);
    moveLeft = true;
    moveRight = false;
  }
  if (y >= 0 && y < 5) {
    digitalWrite(Up, HIGH);
  }

  moveUp = true;
  moveDown = false;

  if (x <= 10 && x > 5) {
    digitalWrite(Right, HIGH);
    moveLeft = false;
    moveRight = true;
  }

  if (y <= 10 && y > 5) {
    digitalWrite(Down, HIGH);
    moveUp = false;
    moveDown = true;
  }

  if (x == 5) {
    digitalWrite(Left, LOW);
    digitalWrite(Right, LOW);
    moveLeft = false;
    moveRight = false;
  }
  if (y == 5) {
    digitalWrite(Up, LOW);
    digitalWrite(Down, LOW);
    moveUp = false;
    moveDown = false;
  }

  if (moveLeft && posx < 180)
  {
    posx = posx + motorSpeed;
  }
  else if (moveRight && posx > 0)
  {
    posx = posx - motorSpeed;
  }
  if (moveUp && posy < 180)
  {
    posy = posy + motorSpeed;
  }
  else if (moveDown && posy > 0)
  {
    posy = posy - motorSpeed;
  }
}

void setup() {
  servox.attach(9);
  servoy.attach(12);
  pinMode(SwButtonPin, INPUT);//sets the SW switch as input
  pinMode(Up, OUTPUT);
  pinMode(Down, OUTPUT);
  pinMode(Left, OUTPUT);
  pinMode(Right, OUTPUT);
  digitalWrite(SwButtonPin, HIGH);//sets the SW button HIGH
  Serial.begin(9600);//sets the baud rate
}

void loop() {
  readJoystick();//calls this function which reads the digital input button SW, the X-coordinate and the Y-coordinate

  if (pressed == 0) {
    userControl = !userControl;
  }

  if (userControl == true) {
    controlStep(5);
  }

  else if (userControl == false) {
    sweepStep(180, 0, 1);
  }
  delay(15);

}
