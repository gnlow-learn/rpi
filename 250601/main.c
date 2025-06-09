#include "gpio.c"

/*
    IO 과정에서 문제가 생겼을 시
    프로그램을 종료하도록
    매크로를 작성하였다.
*/

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

    /* 초기 프로그램 시작 시 GPIO export 및 direction 설정을 수행한다. */

    export(pout1);
    export(pout2);
    export(pin);

    out(pout1);
    out(pout2);
    in(pin);

    /* 반복 간격과 횟수를 설정한다. */

    int tick_us = 1e3;
    int repeat = 1e6;

    /* 버튼을 누르고 있는 시간과 LED 점등 여부를 변수로 저장한다. */
    
    int clicked_us = 0;
    int light = 0;

    do {
        /* light 변수에 따라 LED를 제어한다. */
        write(pout1, light);
        write(pout2, 1);

        if (read(pin) == 0) {
            /* 버튼을 누르고 있을 때 */

            /*
                버튼을 누르고 있는 시간이 800ms를 초과할 경우
                LED on/off를 500ms마다 반복한다.
            */
            if (clicked_us >= 800e3) {
                light = !((int)((float)(clicked_us-800e3)/500e3)%2);
            }

            /* 100ms마다 상태를 출력한다. */
            if (clicked_us % (int)(100e3) == 0) {
                printf("%.0fms, light: %d\n",
                    (float)clicked_us/1e3,
                    light
                );
            }

            /* 버튼을 누르고 있는 시간을 업데이트한다. */
            clicked_us += tick_us;
        } else {
            /* 버튼을 누르고 있지 않을 때 */

            /* 버튼을 눌렀다 땠을 때 LED on/off를 전환한다. */
            if (clicked_us != 0 && clicked_us < 800e3) {
                light ^= 1;
            }

            /* 버튼을 누르고 있는 시간을 초기화 한다. */
            clicked_us = 0;
        }
        
        usleep(tick_us);
    } while (repeat--);

    unexport(pout1);
    unexport(pout2);
    unexport(pin);
    
    return 0;
}
