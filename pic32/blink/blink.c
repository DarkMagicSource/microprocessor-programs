// Blink RB3 and 15

#include <xc.h>

int main() {
    TRISBCLR = 0x8008;
    LATBbits.LATB3 = 0;
    LATBbits.LATB15 = 0;

    while (1) {
        for (int i = 0x0000; i < 0xFFFF; i++) {;}
        LATBINV = 0x8008;
    }
    return 0;
}
