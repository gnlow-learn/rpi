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
    int pout1 = 17;
    int pout2 = 21;
    int pin = 20;
    
    int repeat = 100;
    int state = 1; 
    int prev_state = 1;
    int light = 0;

    export(pout1);
    export(pout2);
    export(pin);

    out(pout1);
    out(pout2);
    in(pin);

    do {
        write(pout2, 1);
        printf("GPIORead: %d from pin %d\n", read(pin), pin);
        write(pout1, read(pin));
        usleep(1000 * 1000);
    } 
    while (repeat--);

    unexport(pout1);
    unexport(pout2);
    unexport(pin);
    
    return 0;
}
