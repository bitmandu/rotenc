/**
 * uart.h
 *
 * UART function declarations.
 **/

#pragma once

#include <stdio.h>

void uart_init(void);
int uart_rx(FILE*);
int uart_tx(char, FILE*);
