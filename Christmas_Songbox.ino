/*
Christmas shining LED MusicBox
Description: LEDs on Christmas tree will blink after power on.
Push buttons will play different songs in wave format.(8bits, 16,000Hz, mono) 
Parts:
- Arduino Nano 3.0
- SD card module (SPI)
- Sound amplifier module (LM386 gain20)
- 8ohm 2W little speaker
- 2 buttons (to trigger music playing)
- 8 LEDs on Christmas Tree

Author: Terence
Date: Dec. 2014

- Thanks to TMRpcm library url: https://github.com/TMRh20/TMRpcm.git
*/

#include <TMRpcm.h>
#include <SD.h>

File myFile;
TMRpcm tmrpcm;

void setup() {
  Serial.begin(9600);
  Serial.println("Initial SD Card...");
  pinMode(10, OUTPUT);
  
  // chekc if the SD card exists and is usable
  if (!SD.begin(4))
  {
    Serial.println("Card failed, or not present");
    // stop sketch
    return;
  }
  Serial.println("SD card is ready");
  
  // check if Wave files existing:
  if(SD.exists("song2.wav")) {
    Serial.println("song2.wav exists.");
  }
  else {
    Serial.println("song2.wav doesn't exist.");
  }
  if(SD.exists("song3.wav")) {
    Serial.println("song3.wav exists.");
  }
  else {
    Serial.println("song3.wav doesn't exist.");
  }
  
  tmrpcm.speakerPin = 9;  // set speaker pin for tmrpcm
  delay(100);
  //Serial.println("Playing song3...");
  //tmrpcm.play("song3.wav");
  pinMode(8, INPUT_PULLUP);  // pull pin high for checking button pushed
  pinMode(7, INPUT_PULLUP);
  
  // LED pin definition
  randomSeed(analogRead(0));
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
}

void ledShine() {
  int randomNumber = random(1, 9);
  switch(randomNumber) {
    case 1:
      ledBlink(2);
      break;
    case 2:
      ledBlink(3);
      break;
    case 3:
      ledBlink(5);
      break;
    case 4:
      ledBlink(6);
      break;
    case 5:
      ledBlink(A5);
      break;
    case 6:
      ledBlink(A4);
      break;
    case 7:
      ledBlink(A3);
      break;
    case 8:
      ledBlink(A2);
      break;
  }
}

void ledBlink(int ledpin) {
  digitalWrite(ledpin, HIGH);
  delay(300);
  digitalWrite(ledpin, LOW);
  delay(50);
}

// 2 LEDs shinging with song tempo (e.g. 500 = 1/2sec => tempo 120)
void ledDance(int period) {
  int randomNumber = random(1, 5);
  switch(randomNumber) {
    case 1:
      digitalWrite(2 ,HIGH);
      digitalWrite(A5 ,HIGH);
      delay(period);
      digitalWrite(2, LOW);
      digitalWrite(A5, LOW);
      delay(period);
      break;
    case 2:
      digitalWrite(3 ,HIGH);
      digitalWrite(A4 ,HIGH);
      delay(period);
      digitalWrite(3, LOW);
      digitalWrite(A4, LOW);
      delay(period);
      break;
    case 3:
      digitalWrite(5 ,HIGH);
      digitalWrite(A3 ,HIGH);
      delay(period);
      digitalWrite(5, LOW);
      digitalWrite(A3, LOW);
      delay(period);
      break;
    case 4:
      digitalWrite(6 ,HIGH);
      digitalWrite(A2 ,HIGH);
      delay(period);
      digitalWrite(6, LOW);
      digitalWrite(A2, LOW);
      delay(period);
      break;
  }
}

void loop() { 
  if(digitalRead(7) == LOW) {
    delay(100);
    tmrpcm.play("song2.wav");
    Serial.println("Song2 is playing...");
    // Change LED play mode
    while(tmrpcm.isPlaying() == 1) {
      ledDance(500);
    }
  }
  else if(digitalRead(8) == LOW) {
    delay(100);
    tmrpcm.play("song3.wav");
    Serial.println("Song3 is playing...");
    
    while(tmrpcm.isPlaying() == 1) {
      ledDance(480);
    }
  }
  else {
    ledShine();
  }
}
  
