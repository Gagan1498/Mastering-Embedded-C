/*GPIO Bit Field Struct
Same register layout as before:
Bits 0-3 → direction (4 pins, 1=output 0=input)
Bits 4-5 → pullup (2 pins, 1=enabled)
Bits 6-7 → reserved
Write a program that:

Declares a bit field struct GPIOReg_t with direction : 4, pullup : 2, reserved : 2
Declares a variable of that type, initialized to all zeros
Sets pins 0 and 2 as outputs — direction = 0b0101
Enables both pull-ups — pullup = 0b11
Toggles the direction field
Clears pull-ups back to 0
Prints binary and hex after each operation using the pointer cast trick for print_binary

Rules:

Reuse print_binary from yesterday
Use the pointer cast to pass the struct to print_binary
Print hex using the same pointer: printf("0x%x\n", *p)*/

#include <stdio.h>
#include <stdint.h>

typedef struct{
    uint8_t Direction : 4;
    uint8_t pullup : 2;
    uint8_t reservedbits : 2;
}GPIOReg_t;

void print_binary(uint8_t val) {
    printf("Value in binary: 0b");
    for (int i = 7; i >= 0; i--)
        printf("%d", (val >> i) & 1);
    printf("\n\n");
}

int main(){

    GPIOReg_t regs = {0};
    uint8_t *p = (uint8_t *)&regs;

    printf("Value in hex: %x\n", *p);
    print_binary(*p);

    regs.Direction = 0b0101;
    printf("Value in hex after setting Pin0 and Pin2 as outputs: %x\n", *p);
    print_binary(*p);

    regs.pullup = 0b11;
    printf("Value in hex after enabling both pullups: %x\n", *p);
    print_binary(*p);

    regs.Direction ^= 0b1111;
    printf("Value in hex after toggling the directions of the pins: %x\n", *p);
    print_binary(*p);

    regs.pullup &= 0b00;
    printf("Value in hex after clearing all pullups: %x\n", *p);
    print_binary(*p);

    return 0;
}