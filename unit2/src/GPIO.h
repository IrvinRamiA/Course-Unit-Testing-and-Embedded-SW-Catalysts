#ifndef GPIO_H
#define GPIO_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;

uint8_t GPIO_SetPinAsOutput(uint8_t pin);
uint8_t GPIO_SetPinAsInput(uint8_t pin);

uint8_t GPIO_SetPin(uint8_t pin);
uint8_t GPIO_ClearPin(uint8_t pin);

uint8_t GPIO_ReadPin();
uint8_t GPIO_ReadPort();

#endif
