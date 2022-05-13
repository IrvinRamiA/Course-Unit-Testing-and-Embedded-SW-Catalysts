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

uint8_t GPIO_SetPin(uint8_t pin)
{
    uint32_t mask = BIT_TO_MASK(pin);

    if (mask == 0)
    {
        return 1;
    }

    PORTC.PSOR = mask;

    if (!(PORTC.PDDR & mask))
    {
        PORTC.PDDR |= mask;
    }

    return 0;
}

uint8_t GPIO_ClearPin(uint8_t pin)
{
    uint32_t mask = BIT_TO_MASK(pin);

    if (mask == 0)
    {
        return 1;
    }

    PORTC.PCOR = mask;

    /* PDDR -> 1: Output, 0: Input*/
    if (!(PORTC.PDDR & mask))
    {
        PORTC.PDDR |= mask;
    }

    return 0;
}
