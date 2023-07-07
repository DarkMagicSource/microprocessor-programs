# Alternate blinking of RB3 and 15

#include <xc.h>

.set noreorder
.text
.globl main

main:
    li t0, 0x8008
    sw t0, TRISBCLR

    li t0, 0x1 << 15
    sw t0, LATB

loop:
    li t0, 0x8008
    sw t0, LATBINV

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
