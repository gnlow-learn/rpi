#include "gpio.c"

#define export(p) do { \
    if (GPIOExport(p) == -1) return 1; \
} while (0)

#define out(p) do { \
    if (GPIODirection(p, OUT) == -1) return 1; \
} while (0)

#define in(p) do { \
    if (GPIODirection(p, IN) == -1) return 2; \
} while (0)

#define write(p, x) do { \
    if (GPIOWrite(p, x) == -1) return 3; \
} while (0)

#define read(p) GPIORead(p)

#define unexport(p) do { \
    if (GPIOUnexport(p) == -1) return 4; \
} while (0)

int main(int argc, char* argv[]) {
    int pout1 = 17; // LED
    int pout2 = 21; // Button
    int pin = 20;
    
    int repeat = 1e6;

    export(pout1);
    export(pout2);
    export(pin);

    out(pout1);
    out(pout2);
    in(pin);

    int tick_us = 1e3;
    int clicked_us = 0;
    int light = 0;

    do {
        write(pout1, light);
        write(pout2, 1);
        if (read(pin) == 0) {
            if (clicked_us == 0) {
                light ^= 1;
            }
            clicked_us += tick_us;
            printf("%.0fms\n", (float)clicked_us/1e3);
            write(pout1, 1);
        } else {
            clicked_us = 0;
        }
        usleep(tick_us);
    } while (repeat--);

    unexport(pout1);
    unexport(pout2);
    unexport(pin);
    
    return 0;
}
