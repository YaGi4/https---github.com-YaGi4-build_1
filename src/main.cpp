//#include <Arduino.h>
#include "function.h"

#define PIN_IN1 5
#define PIN_IN3 6
#define PIN_WHEEL_RIGHT 7    // пин управления мощностью правого двигателя (изменяется в предалах 0 - 255)
#define PIN_WHEEL_LEFT 9     // пин управления мощностью левого двигателя (изменяется в предалах 0 - 255)
#define PIN_DATR 20    // пин с digital показаниями правого датчика линии (принимает значение 0 - когда видит черную линию)
#define PIN_DATM 3     // пин с digital показаниями левого датчика линии (принимает значение 0 - когда видит черную линию)
#define PIN_DATL 21    // пин с digital показаниями среднего датчика линии (принимает значение 0 - когда видит черную линию)
int scode[7] = {2,2,2,2,2,2,2};
int flag = 0;
volatile int speedLeft = 100;
volatile int speedRight = 80;




void turnLeft() // при обнаружении (левым датчиком) черной линии будет поварачивать машинку пока не произойдет следующее прерывание
{
  //volatile boolean left = digitalRead(PIN_DATL);
  speedLeft = 0;
  speedRight = 90;
}

void turnRight() // при обнаружении (правым датчиком) черной линии будет поварачивать машинку пока не произойдет следующее прерывание
{
  //volatile boolean right = digitalRead(PIN_DATR);
  speedLeft = 90;
  speedRight = 0;
}
void forvard() // при обнаружении (средним датчиком) черной линии будет поварачивать машинку пока не произойдет следующее прерывание
{
 // volatile boolean forv = digitalRead(PIN_DATM);
  speedLeft = 160;
  speedRight = 140;
}

void setup() 
{ 
  Serial.begin(9600);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_WHEEL_RIGHT, OUTPUT);
  pinMode(PIN_WHEEL_LEFT, OUTPUT);
  pinMode(PIN_DATR, INPUT);
  pinMode(PIN_DATM, INPUT);
  pinMode(PIN_DATL, INPUT);
  attachInterrupt(2, turnLeft, CHANGE);
  attachInterrupt(3, turnRight, CHANGE);
  attachInterrupt(1, forvard, CHANGE);
}

void set_car_speed(int sl, int sr)        // 1 - скорость левого колеса 2 - скорость правого колеса
{                                         // ф-ия заставляет машинку двигаться с заданой скоростью  
  analogWrite(PIN_WHEEL_RIGHT, sr);
  analogWrite(PIN_WHEEL_LEFT, sl);
}
void speeds(int sp1, int sp2) {
  speedLeft=sp1;
  speedRight=sp2;
}

/*int yield(int i) {
  i++;
  scode[i]=digitalRead(PIN_DATM);
  return i;
}*/

void datch() 
{
    
    /*set_car_speed(0,0);
    delay(500);*/
    for (int i = 1; scode[7]==2; i++)
    { 
      
      while (scode[i]==2) {
      set_car_speed(100, 80);
      if (digitalRead(PIN_DATL)==1 && digitalRead(PIN_DATR)==1 && digitalRead(PIN_DATM)==1)
      {
        set_car_speed(0, 0);
        scode[i]=1;
      }
      if (digitalRead(PIN_DATL)==0 && digitalRead(PIN_DATR)==0 && digitalRead(PIN_DATM)==0)
      {
        set_car_speed(0, 0);
        scode[i]=0;
      }
      }
      
    }
    if (scode[7]!=2) flag = 2;
    /*if (scode[7] == 2) 
      {
        set_car_speed(90, 100);
        if (digitalRead(PIN_DATL)==1 && digitalRead(PIN_DATR)==1 && digitalRead(PIN_DATM)==1)
          { 
            set_car_speed(0,0);
            delay(500);
            scode[7]=0;
            interrupts();
          }

    } */
}

void loop() 
{
  set_car_speed(speedLeft, speedRight); 
  if (flag == 0 && digitalRead(PIN_DATL)==0 && digitalRead(PIN_DATR)==0 && digitalRead(PIN_DATM)==0) 
  { 
    set_car_speed(0,0);
    scode[0]=0;
    noInterrupts();
    //datch();
    flag=1;
  }
  
  while (flag == 1) 
  { 
   noInterrupts();
    datch();
  }
  //if (flag == 2) interrupts();
} 