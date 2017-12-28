#include <Arduino.h>
const byte PIN_DIGIT_1 = 2;
const byte PIN_DIGIT_2 = 3;
const byte PIN_DIGIT_3 = 4;
const byte PIN_DIGIT_4 = 5;

const byte PIN_SEGMENT_DP = 6;

const byte PIN_SEGMENT_A = 7;
const byte PIN_SEGMENT_B = 8;
const byte PIN_SEGMENT_C = 9;
const byte PIN_SEGMENT_D = 10;
const byte PIN_SEGMENT_E = 11;
const byte PIN_SEGMENT_F = 12;
const byte PIN_SEGMENT_G = 13;

const byte PIN_POTENTIOMETRE = A1;



//bitRead(segments,position)
void afficherSegments(int chiffre, boolean DP){
  byte segments;
  const byte INT_TO_SEGMENTS[] ={
    0b1111110,
    0b0110000,
    0b1101101,
    0b1111001,
    0b0110011,
    0b1011011,
    0b1011111,
    0b1110000,
    0b1111111,
    0b1111011
  };
  segments = INT_TO_SEGMENTS[chiffre];
  if(DP){
    digitalWrite(PIN_SEGMENT_DP, HIGH);
  }
  else{
    digitalWrite(PIN_SEGMENT_DP, LOW);
  }
  digitalWrite(PIN_SEGMENT_A,bitRead(segments,6));
  digitalWrite(PIN_SEGMENT_B,bitRead(segments,5));
  digitalWrite(PIN_SEGMENT_C,bitRead(segments,4));
  digitalWrite(PIN_SEGMENT_D,bitRead(segments,3));
  digitalWrite(PIN_SEGMENT_E,bitRead(segments,2));
  digitalWrite(PIN_SEGMENT_F,bitRead(segments,1));
  digitalWrite(PIN_SEGMENT_G,bitRead(segments,0));


}

void clearDigits(){
  digitalWrite(PIN_DIGIT_1,HIGH);
  digitalWrite(PIN_DIGIT_2,HIGH);
  digitalWrite(PIN_DIGIT_3,HIGH);
  digitalWrite(PIN_DIGIT_4,HIGH);
}

void afficherDigits(int digit){
  switch(digit){
    case 0:
      digitalWrite(PIN_DIGIT_1,LOW);
      break;
    case 1:
      digitalWrite(PIN_DIGIT_2,LOW);
      break;
    case 2:
      digitalWrite(PIN_DIGIT_3,LOW);
      break;
    case 3:
      digitalWrite(PIN_DIGIT_4,LOW);
      break;
  }
}

//nbAff = nombre a afficher ; dpPos = position du point ; t = temps entre chaque digit
void afficherNombre(int nbAff, int dpPos, int t){
  int chiffre1 = (nbAff /1000)%10;
  int chiffre2 = (nbAff /100)%10;
  int chiffre3 = (nbAff /10)%10;
  int chiffre4 = nbAff %10 ;
  boolean dp1;

  //dp1 = (dpPos == 0 ? true : false); =>Tour de manège
 /* if(dpPos == 0){
    dp1 = true;
  }else{
    dp1 = false;
  }*/

  clearDigits();
  afficherSegments(chiffre1,dpPos == 0);
  afficherDigits(0);
  delay(t);
  clearDigits();
  afficherSegments(chiffre2,dpPos == 1);
  afficherDigits(1);
  delay(t);
  clearDigits();
  afficherSegments(chiffre3,dpPos == 2);
  afficherDigits(2);
  delay(t);
  clearDigits();
  afficherSegments(chiffre4,dpPos == 3);
  afficherDigits(3);
  delay(t);
}


void setup(){
  // put your setup code here, to run once:

  pinMode(PIN_DIGIT_1, OUTPUT);
  pinMode(PIN_DIGIT_2, OUTPUT);
  pinMode(PIN_DIGIT_3, OUTPUT);
  pinMode(PIN_DIGIT_4, OUTPUT);
  pinMode(PIN_SEGMENT_DP, OUTPUT);
  pinMode(PIN_SEGMENT_A, OUTPUT);
  pinMode(PIN_SEGMENT_B, OUTPUT);
  pinMode(PIN_SEGMENT_C, OUTPUT);
  pinMode(PIN_SEGMENT_D, OUTPUT);
  pinMode(PIN_SEGMENT_E, OUTPUT);
  pinMode(PIN_SEGMENT_F, OUTPUT);
  pinMode(PIN_SEGMENT_G, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
int vP = analogRead(PIN_POTENTIOMETRE);//vP = valeur du potentiometre avec 1023 = 5v et 0 = 0v
afficherNombre(vP,-1,vP);

}
