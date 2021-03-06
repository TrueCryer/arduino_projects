
/* import pithes for alarm */
#include "pitches.h"


int ledBlue = 7;   /* Warming up */
int ledRed = 4;    /* Alarm */
int ledGreen = 2;  /* OK */

int buzzer = 8;    /* Buzzer pin */
int breaker = 12;  /* Breaker button pin */

int gasAnalog = 0;  /* Pin for gas sensor */
int potAnalog = 1;  /* Pin for potentiometer */

int gas = 0;  /* Gas level */
int pot = 0;  /* Potentiometer level */

int breakDelay = 0; /* Break delay in number of cycles */


void playAlarm() {
  
  tone(buzzer, NOTE_E4); delay(250);
  tone(buzzer, NOTE_C4); delay(250);
  tone(buzzer, NOTE_E4); delay(250);
  tone(buzzer, NOTE_C4); delay(250);
  tone(buzzer, NOTE_F4); delay(250);
  tone(buzzer, NOTE_E4); delay(250);
  tone(buzzer, NOTE_D4); delay(500);
  
  noTone(buzzer); delay(500);

}


void setup() {

  /* Set pin modes
   */
  pinMode(ledRed,   OUTPUT);
  pinMode(ledBlue,  OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(breaker,  INPUT);

  /* While gas detector warming up,
   *  blinking 20 seconds
   */
  for (int x = 0; x < 10; x++) {
    digitalWrite(ledBlue, HIGH);
    delay(1000);
    digitalWrite(ledBlue, LOW);
    delay(1000);
  }

  Serial.begin(9600);

}


void loop() {
  
  /* Update breaking data */
  if (digitalRead(breaker) > 0) {
    breakDelay = 120; /* 120 seconds, if cycle == 1 sec */
  }

  /* Read gas level */
  gas = analogRead(gasAnalog);
  pot = analogRead(potAnalog);

  if (gas + pot >= 1024) {  /* Danger */

    /* Light Red LED */
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);

    if (breakDelay > 0) { /* Breaker is activated, don't alarm */
      breakDelay -= 1;
    } else {
      playAlarm();
    };

  } else {

    /* Light Green LED */
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);

  }

  /* Backlog */
  Serial.print("Gas level: ");
  Serial.print(gas);
  Serial.print(", Potentiometer level: ");
  Serial.println(pot);

  /* Delay */
  delay(1000);

}
