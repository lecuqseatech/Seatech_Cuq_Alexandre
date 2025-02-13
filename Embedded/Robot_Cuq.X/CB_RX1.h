/* 
 * File:   CB_RX1.h
 * Author: E306-PC4
 *
 * Created on 22 janvier 2025, 17:07
 */

#ifndef CB_RX1_H
#define	CB_RX1_H
void CB_RX1_Add(unsigned char value);
unsigned char CB_RX1_Get(void);
unsigned char CB_RX1_IsDataAvailable(void);
int CB_RX1_GetDataSize(void);
int CB_RX1_GetRemainingSize(void);
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);
#endif	/* CB_RX1_H */

