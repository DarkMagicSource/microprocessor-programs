# Blink RB3 and 15

#include <xc.h>

#define ON 0xFFFF
#define OFF 0x0000

.set noreorder
.text
.globl main

main:
    li t0, 0x7FF7
    sw t0, TRISB

loop:
    li t0, OFF
    sw t0, LATB

    jal delay
    nop

    li t0, ON
    sw t0, LATB

    jal delay
    nop

    j loop
    nop

delay:
    li t2, 0xFFFFF
delay_loop:
    addi t2, t2, -1
    bnez t2, delay_loop
    nop
    jr ra
    nop
