#include <ServoTimer2.h>
#define IR_USE_AVR_TIMER1
#include <IRremote.h>
#include <Stepper.h>
#include <pitches.h>


const int buzzer = 2;
const int IR_RECEIVE_PIN = 9;
const int ledOne = 4;
const int ledTwo = 10;
const int ledThree = 11;
const int ledFour = 12;
const int ledFive = 13;
const int stepsPerRevolution = 2038;

ServoTimer2 myservo;
Stepper myStepper = Stepper(stepsPerRevolution, 5, 7, 6, 8);


int remoteData;
int previousData = 0;
int ledState = 0;
int ledMode;
int pos = 0; 
int beepTone = 1000;


bool ledSwitch = false;
bool servSwitch = false;
bool stepSwitch = false;
bool beepSwitch = false;

int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

int durations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

int melody2[] = {
  NOTE_C4, NOTE_C4, 
  NOTE_D4, NOTE_C4, NOTE_F4,
  NOTE_E4, NOTE_C4, NOTE_C4, 
  NOTE_D4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_C4, NOTE_C4,
  
  NOTE_C5, NOTE_A4, NOTE_F4, 
  NOTE_E4, NOTE_D4, NOTE_AS4, NOTE_AS4,
  NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_F4
};

int durations2[] = {
  4, 8, 
  4, 4, 4,
  2, 4, 8, 
  4, 4, 4,
  2, 4, 8,
  
  4, 4, 4, 
  4, 4, 4, 8,
  4, 4, 4,
  2
};


void setup() {
  Serial.begin(9600);
  myservo.attach(3);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  pinMode(ledFour, OUTPUT);
  pinMode(ledFive, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  irData();
}

void irData() {
  if (IrReceiver.decode()) {
    delay(500);
    IrReceiver.resume();
    remoteData = IrReceiver.decodedIRData.command;
    Serial.println(remoteData);
    switch (remoteData) {
      case 69:
      ledShow();
      break;
      case 22:
      ledAll();
      break;
      case 12:
      ledFirst();
      break;
      case 24:
      ledSecond();
      break;
      case 94:
      ledThird();
      break;
      case 8:
      ledFourth();
      break;
      case 28:
      ledFifth();
      break;
      case 90:
      myservo.write(750);
      delay(1000);             
      servoSwitch();
      break;
      case 66:
      stepperSwitch();
      break;
      case 82:
      beepToggle();
      break;
      case 70:
      beepLow();
      break;
      case 71:
      beepHigh();
      break;
      case 68:
      servoLeft();
      break;
      case 64:
      servoRight();
      break;
      case 67:
      servoToggle();
      break;
      case 7:
      stepperRight();
      break;
      case 21:
      stepperLeft();
      break;
      case 9:
      stepperToggle();
      break;
      case 25:
      animateOne();
      break;
      case 13:
      animateTwo();
      break;
      case 74:
      rollingPitch();
      break;
    }
  }
}

void ledShow() {
  if (remoteData == previousData && ledState == 0) {
    digitalWrite(ledOne, HIGH);
    digitalWrite(ledTwo, LOW);
    digitalWrite(ledThree, LOW);
    digitalWrite(ledFour, LOW);
    digitalWrite(ledFive, LOW);
    ledState++;
    previousData = remoteData;
    Serial.println(ledState);
  }
  else if (remoteData == previousData && ledState == 1) {
    digitalWrite(ledOne, LOW);
    digitalWrite(ledTwo, HIGH);
    digitalWrite(ledThree, LOW);
    digitalWrite(ledFour, LOW);
    digitalWrite(ledFive, LOW);
    ledState++;
    previousData = remoteData;
    Serial.println(ledState);
  }
  else if (remoteData == previousData && ledState == 2) {
    digitalWrite(ledOne, LOW);
    digitalWrite(ledTwo, LOW);
    digitalWrite(ledThree, HIGH);
    digitalWrite(ledFour, LOW);
    digitalWrite(ledFive, LOW);
    ledState++;
    previousData = remoteData;
    Serial.println(ledState);
  }
  else if (remoteData == previousData && ledState == 3) {
    digitalWrite(ledOne, LOW);
    digitalWrite(ledTwo, LOW);
    digitalWrite(ledThree, LOW);
    digitalWrite(ledFour, HIGH);
    digitalWrite(ledFive, LOW);
    ledState++;
    previousData = remoteData;
    Serial.println(ledState);
  }
  else if (remoteData == previousData && ledState == 4) {
    digitalWrite(ledOne, LOW);
    digitalWrite(ledTwo, LOW);
    digitalWrite(ledThree, LOW);
    digitalWrite(ledFour, LOW);
    digitalWrite(ledFive, HIGH);
    ledState++;
    previousData = remoteData;
    Serial.println(ledState);
  }
  else {
    digitalWrite(ledOne, HIGH);
    digitalWrite(ledTwo, HIGH);
    digitalWrite(ledThree, HIGH);
    digitalWrite(ledFour, HIGH);
    digitalWrite(ledFive, HIGH);
    ledState = 0;
    previousData = remoteData;
    Serial.println(ledState);
  }
}

void ledOff() {
  digitalWrite(ledOne, LOW);
  digitalWrite(ledTwo, LOW);
  digitalWrite(ledThree, LOW);
  digitalWrite(ledFour, LOW);
  digitalWrite(ledFive, LOW);
  previousData = 0;
}

void ledAll() {
  if (remoteData != previousData) {
     digitalWrite(ledOne, HIGH);
      digitalWrite(ledTwo, HIGH);
      digitalWrite(ledThree, HIGH);
      digitalWrite(ledFour, HIGH);
      digitalWrite(ledFive, HIGH);
      previousData = remoteData;
  }
  else {
    ledOff();
  }
}

void ledFirst() {
  if (remoteData != previousData) {
      digitalWrite(ledOne, HIGH);
      digitalWrite(ledTwo, LOW);
      digitalWrite(ledThree, LOW);
      digitalWrite(ledFour, LOW);
      digitalWrite(ledFive, LOW);
      previousData = remoteData;
  }
  else {
    ledOff();
  }
}

void ledSecond() {
  if (remoteData != previousData) {
      digitalWrite(ledOne, LOW);
      digitalWrite(ledTwo, HIGH);
      digitalWrite(ledThree, LOW);
      digitalWrite(ledFour, LOW);
      digitalWrite(ledFive, LOW);
      previousData = remoteData;
  }
  else {
    ledOff();
  }
}

void ledThird() {
  if (remoteData != previousData) {
      digitalWrite(ledOne, LOW);
      digitalWrite(ledTwo, LOW);
      digitalWrite(ledThree, HIGH);
      digitalWrite(ledFour, LOW);
      digitalWrite(ledFive, LOW);
      previousData = remoteData;
  }
  else {
    ledOff();
  }
}

void ledFourth() {
  if (remoteData != previousData) {
      digitalWrite(ledOne, LOW);
      digitalWrite(ledTwo, LOW);
      digitalWrite(ledThree, LOW);
      digitalWrite(ledFour, HIGH);
      digitalWrite(ledFive, LOW);
      previousData = remoteData;
  }
  else {
    ledOff();
  }
}

void ledFifth() {
  if (remoteData != previousData) {
      digitalWrite(ledOne, LOW);
      digitalWrite(ledTwo, LOW);
      digitalWrite(ledThree, LOW);
      digitalWrite(ledFour, LOW);
      digitalWrite(ledFive, HIGH);
      previousData = remoteData;
  }
  else {
    ledOff();
  }
}

void servoSwitch() {
  if (servSwitch == false) {
    myservo.write(750);              // tell servo to go to position in variable 'pos'
    delay(1000);                       // waits 15ms for the servo to reach the position
    servSwitch = true;
  }
  else {
    myservo.write(2250);              // tell servo to go to position in variable 'pos'
    delay(1000);                       // waits 15ms for the servo to reach the position
    servSwitch = false;
  }
}

void servoLeft() {
    myservo.write(750);              // tell servo to go to position in variable 'pos'
    delay(1000);                       // waits 15ms for the servo to reach the position
}

void servoRight() {
    myservo.write(2250);              // tell servo to go to position in variable 'pos'
    delay(1000); 
}

void stepperSwitch() {
  if (stepSwitch == false) {
	  myStepper.setSpeed(10);
	  myStepper.step(stepsPerRevolution);
	  delay(1000);
    stepSwitch = !stepSwitch;
  }
  else {
    myStepper.setSpeed(10);
	  myStepper.step(-stepsPerRevolution);
	  delay(1000);
    stepSwitch = !stepSwitch;
  }
}

void beepToggle() {
  for (int x = 0; x <= 100; x++) {
    tone(buzzer, beepTone); // Send 1KHz sound signal...
    delay(5);
    noTone(buzzer);
    delay(5);
  }
  ledOff();
}

void beepLow() {
  beepTone -= 200;
  tone(buzzer, beepTone);
  delay(1000);
  noTone(buzzer);
  delay(1000);
}

void beepHigh() {
  beepTone += 200;
  tone(buzzer, beepTone);
  delay(1000);
  noTone(buzzer);
  delay(1000);
}

void servoToggle() {
    myservo.write(2250);              // tell servo to go to position in variable 'pos'
    delay(1000); 
    myservo.write(750);              // tell servo to go to position in variable 'pos'
    delay(1000); 
}

void stepperLeft(){
  	myStepper.setSpeed(10);
	  myStepper.step(-stepsPerRevolution);
	  delay(1000);
}

void stepperRight() {
    myStepper.setSpeed(10);
	  myStepper.step(stepsPerRevolution);
	  delay(1000);
}

void stepperToggle() {
  	myStepper.setSpeed(10);
	  myStepper.step(-stepsPerRevolution);
	  delay(1000);
	  myStepper.step(stepsPerRevolution);
	  delay(1000);
}

void animateOne() {
 int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(buzzer, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    //stop the tone playing:
    noTone(buzzer);
  }
}

void animateTwo() {

  int size = sizeof(durations2) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations2[note];
    tone(buzzer, melody2[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    //stop the tone playing:
    noTone(buzzer);
  }
}

void rollingPitch() {
  for (beepTone = 100; beepTone <= 65000; beepTone += 1000) {
    tone(buzzer, beepTone);
    delay(100);
    noTone(buzzer);
    delay(100);
  }
  for (beepTone = 65000; beepTone >= 100; beepTone -= 1000) {
    tone(buzzer, beepTone);
    delay(100);
    noTone(buzzer);
    delay(100);
  } 
}