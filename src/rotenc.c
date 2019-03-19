/**
 * @file rotenc.c
 *
 * Rotary encoder.
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

#define ROTENC_DDR DDRC    /**< Rotary encoder data direction registers */
#define ROTENC_PORT PORTC  /**< Rotary encoder interrupt port */
#define ROTENC_PIN PINC    /**< Rotary encoder pin registers */
#define ROTENC_A PCINT8    /**< Rotary encoder pin A */
#define ROTENC_B PCINT9    /**< Rotary encoder pin B */

/**
 * Enable PCINT1 interrupts (pins PCINT8-PCINT14).
 */
void pcint1_init(void)
{
    PCICR |= (1 << PCIE1);      // interrupt on C pins
    PCMSK1 |= (1 << ROTENC_A);  // interrupt on pin ROTENC_A
}

/**
 * Handle PCINT1 interrupt.
 */
ISR(PCINT1_vect)
{
    uint8_t pinB = bit_is_set(ROTENC_PIN, ROTENC_B);
    char direction;

    if (bit_is_set(ROTENC_PIN, ROTENC_A)) {
        direction = pinB ? '-' : '+';
    } else {
        direction = pinB ? '+' : '-';
    }

    putchar(direction);
}

int main(void)
{
    uart_init();

    /* set rotary encoder pins A and B as input */
    ROTENC_DDR &= ~(1 << ROTENC_A);
    ROTENC_DDR &= ~(1 << ROTENC_B);
    ROTENC_PORT |= (1 << ROTENC_A) | (1 << ROTENC_B);  // pull-up

    /* enable interrupts */
    pcint1_init();
    sei();

    printf("[-- rotenc --]\r\n");

    for (;;) {
        ;
    }

    return 0;
}
