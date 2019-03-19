/**
 * @file uart.c
 *
 * Universal Asynchronous Receiver Transceiver (UART) library.
  */

#include <stdio.h>
#include <avr/io.h>
#include <util/setbaud.h>
#include "uart.h"

static FILE rx = FDEV_SETUP_STREAM(NULL, uart_rx, _FDEV_SETUP_READ);
static FILE tx = FDEV_SETUP_STREAM(uart_tx, NULL, _FDEV_SETUP_WRITE);

/**
 * Initialize serial UART.
 */
void uart_init(void)
{
    // set baud rate; BAUD (used by setbaud.h) must be defined elsewhere
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // 8 data bits, 1 stop bit

    stdin = &rx;
    stdout = &tx;
}

/**
 * Transmit serial data.
 *
 * @param data Character to transmit
 * @param stream Output file stream
 * @return Nonzero on error
 */
int uart_tx(char data, FILE *stream)
{
    if (data == '\n') {
        uart_tx('\r', stream);
    }

    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;

    return 0;
}

/**
 * Receive serial data.
 *
 * @param stream Input file stream
 * @return Byte received
 */
int uart_rx(FILE *stream)
{
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}
