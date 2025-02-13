/* 
 * File:   UART.h
 * Author: E306-PC4
 *
 * Created on 13 janvier 2025, 12:19
 */

#ifndef UART_H
#define UART_H
void InitUART(void);
void SendMessageDirect(unsigned char* message, int length);
//void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);
#endif /* UART_H */

