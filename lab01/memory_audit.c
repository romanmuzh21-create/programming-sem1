#include <stdio.h>

int main(void) {
    printf(" Data Type Sizes \n");
    printf("sizeof(char):        %zu byte(s)\n", sizeof(char));
    printf("sizeof(short):       %zu byte(s)\n", sizeof(short));
    printf("sizeof(int):         %zu byte(s)\n", sizeof(int));
    printf("sizeof(long):        %zu byte(s)\n", sizeof(long));
    printf("sizeof(long long):   %zu byte(s)\n", sizeof(long long));
    printf("sizeof(float):       %zu byte(s)\n", sizeof(float));
    printf("sizeof(double):      %zu byte(s)\n", sizeof(double));
    printf("sizeof(void*):       %zu byte(s)\n\n", sizeof(void*));

    unsigned char byte_test = 255;

    printf("Integer Overflow Demonstration\n");
    printf("Initial value (DEC): %u\n", byte_test);
    printf("Initial value (HEX): 0x%02X\n", byte_test);

    byte_test = byte_test + 1;

    printf("\nAfter adding 1 (byte_test = byte_test + 1):\n");
    printf("New value (DEC):     %u\n", byte_test);
    printf("New value (HEX):     0x%02X\n", byte_test);

    return 0;
}
