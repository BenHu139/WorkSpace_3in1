/*
 * CAN_INTC.h
 *
 *  Created on: Oct 23, 2014
 */

#ifndef CAN_INTC_H_
#define CAN_INTC_H_

void can_buf00_03_interrupt_handler0(void);
void can_buf04_07_interrupt_handler0(void);
void can_buf08_11_interrupt_handler0(void);
void can_buf12_15_interrupt_handler0(void);
void can_buf16_31_interrupt_handler0(void);
void can_buf32_63_interrupt_handler0(void);


void can_buf00_03_interrupt_handler1(void);
void can_buf04_07_interrupt_handler1(void);
void can_buf08_11_interrupt_handler1(void);
void can_buf12_15_interrupt_handler1(void);
void can_buf32_63_interrupt_handler1(void);

#endif /* CAN_INTC_H_ */
