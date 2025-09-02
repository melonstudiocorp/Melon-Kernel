#include <stdint.h>
#include "../core/krnl/krnl.h"

void starfall() {
    char stars[25][80] = {0};
    int i, j;
        while (1) {
        clearline();

        uint8_t key = get_key();
        if (key == 0x01) {
            clearline();
            return;
        }

        for (i = 0; i < 80; i++) {
            stars[0][i] = (rand() % 10 == 0) ? '*' : ' ';
        }

        for (i = 24; i > 0; i--) {
            for (j = 0; j < 80; j++) {
                stars[i][j] = stars[i-1][j];
            }
        }

        for (i = 0; i < 25; i++) {
            outline(stars[i]);
            outline("\n");
        }

        delay(100000000);
    }
}
void spinner() {
    char frames[] = {'|','\\','-','/'};
    while(1) {
        for(int i=0;i<4;i++) {
            clearline();
            char buf[2] = {frames[i],0};
           outline(buf);
            for(volatile int d=0;d<5000000;d++);
            uint8_t key = get_key();
            if (key == 0x01) {
                clearline();
                return;
            }
        }
    }
}