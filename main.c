#include "gpio.c"

int main(int argc, char* argv[]) {
    int pout1 = 17;
    int pout2 = 21;
    int pin = 20;
    
    int repeat = 100;
    int state = 1; 
    int prev_state = 1;
    int light = 0;

    if (0
        || GPIOExport(pout1) == -1
        || GPIOExport(pout2) == -1
        || GPIOExport(pin)
    ) return 1;
    if (0
        || GPIODirection(pout1, OUT) == -1
        || GPIODirection(pout2, OUT) == -1
        || GPIODirection(pin, IN) == -1
    ) return 2;

    do {
        if (GPIOWrite(pout2, 1) == -1) return 3;
        printf("GPIORead: %d from pin %d\n", GPIORead(pin), pin);
        if (GPIOWrite(pout1, GPIORead(pin)) == -1) return 3;
        usleep(1000 * 1000);
    } 
    while (repeat--);
    
    if (0
        || GPIOUnexport(pout1) == -1
        || GPIOUnexport(pout2) == -1
        || GPIOUnexport(pin) == -1
    ) return 4;
    
    return 0;
}



int main2(int argc, char* argv[]) {
    int repeat = 10;
    int pout = 17;
    
    if (GPIOExport(pout) == -1) {
        return 1;
    }
    if (GPIODirection(pout, pout) == -1) {
        return 2;
    }
    do {
        if (GPIOWrite(pout, repeat % 2) == -1) {
            return 3;
        }
        usleep(500 * 1000);
    } while (repeat--);
    if (GPIOUnexport(pout) == -1) {
        return 4;
    }

  return 0;
}
