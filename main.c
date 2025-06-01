#include "gpio.c"

int main(int argc, char* argv[]) {
    int PIN = 20;
    int POUT2 = 21;
    int repeat = 100;
    int state = 1; 
    int prev_state = 1;
    int light = 0;

    if (GPIOExport(POUT2) == -1 || GPIOExport(PIN)) {
        return 1;
    }
    if (GPIODirection(POUT2, OUT) == -1 || GPIODirection(PIN, IN) == -1) {
        return 2;
    }
    do {
        if (GPIOWrite(POUT2, 1) == -1) {
            return 3;
        }
        printf("GPIORead: %d from pin %d\n", GPIORead(PIN), PIN);
        usleep(1000 * 1000);
    } 
    while (repeat--);
    
    if (GPIOUnexport(POUT2) == -1 || GPIOUnexport(PIN) == -1) {
        return 4;
    }
    
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
