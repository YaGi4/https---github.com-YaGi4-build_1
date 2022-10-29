#include <Arduino.h>

/*  A0 заменить на наш пин */ const int IRpin = A0;          // аналоговый пин для подключения выхода Vo сенсора.
int value;                    // для хранения аналогового значения
float volts, distance; //volts - напряжение, distance = расстояние

// Усреднение нескольких значений для сглаживания
int irRead() {
int averaging = 0; // переменная для суммирования данных
// Получение 5 значений
for (int i=0; i<5; i++)
{
value = analogRead(IRpin);
// значение сенсора переводим в напряжение
float volts = analogRead(IRpin)*0.0048828125;
// и в расстояние в см
int distance=32*pow(volts,-1.10);
averaging = averaging + distance;
delay(55); // Ожидание 55 ms перед каждым чтением
}
value = averaging / 5; // усреднить значения
return(value);
}