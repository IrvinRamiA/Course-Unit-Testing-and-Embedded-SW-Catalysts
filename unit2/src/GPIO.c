#include "GPIO.h"
#include "../inc/MK20DX256.h"

uint8_t GPIO_SetPinAsOutput(uint8_t pin)
{
    if (pin >= 32)
    {
        return 1;
    }

    PORTC.PDDR |= BIT_TO_MASK(pin);

    return 0;
}

uint8_t GPIO_SetPinAsInput(uint8_t pin)
{
    if (pin >= 32)
    {
        return 1;
    }

    PORTC.PDDR &= ~(BIT_TO_MASK(pin));
    return 0;
}
