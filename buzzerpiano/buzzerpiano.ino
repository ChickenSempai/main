#include "pitches.h"
#define REST 0
const int button1 = 2;
const int button2 = 4;
const int button3 = 6;
const int button4 = 8;
const int buzzer = 10;
const int led = 11; 

int melodyOH[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};
int durations[] = {
  8, 8, 8, 4, 4, 4,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 4, 4,
  4, 8, 8, 8, 8, 8
};
int songLength = sizeof(melodyOH)/sizeof(melodyOH[0]);

int melody[] = {
  
  // Dart Vader theme (Imperial March) - Star wars 

  NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16,

  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,//4
  NOTE_E5,4, NOTE_E5,4, NOTE_E5,4, NOTE_F5,-8, NOTE_C5,16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
  
  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
  NOTE_C5,4, NOTE_A4,-8, NOTE_C5,16, NOTE_E5,2,

  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
  
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;

int tempo = 120;
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;


void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int pitch=0;
  int b1=digitalRead(button1);
  int b2=digitalRead(button2);
  int b3=digitalRead(button3);
  int b4=digitalRead(button4);
  if (b4==HIGH)
    for (int thisNote = 0; thisNote < songLength; thisNote++){
      int duration = 1000/ durations[thisNote];
      tone(buzzer, melodyOH[thisNote], duration);
      int pause = duration * 1.3;
      delay(pause);
      noTone(8);
  }
  else if (b3==HIGH)
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = melody[thisNote + 1];
          if (divider > 0) {
            noteDuration = (wholenote) / divider;
          } 
          else if (divider < 0) {
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5;
          }
      tone(buzzer, melody[thisNote], noteDuration*0.9);
      delay(noteDuration);
      noTone(buzzer);
      }
  else {
    if (b1==HIGH)
      pitch+=400;
    if (b2==HIGH)
      pitch+=400;
    if (pitch>1500)
      pitch=1500;
    if (pitch>0){
      digitalWrite(led, HIGH);
    }
    else digitalWrite(led, LOW);
    tone(buzzer,pitch, 20);
    delay(1);
  }
}
