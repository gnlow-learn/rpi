#include "gpio.c"

int main(int argc, char* argv[]) {
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
