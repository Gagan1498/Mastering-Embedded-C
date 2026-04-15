/*Reinforcement Program — GPIO Port Simulator
You're configuring a GPIO port register on a microcontroller. The register is 8 bits wide:
Bit 7: Reserved
Bit 6: Reserved  
Bit 5: Pull-up enable
Bit 4: Pull-up enable
Bit 3: Direction (1 = output, 0 = input)  pin 3
Bit 2: Direction (1 = output, 0 = input)  pin 2
Bit 1: Direction (1 = output, 0 = input)  pin 1
Bit 0: Direction (1 = output, 0 = input)  pin 0
Your task — write a program that:

Defines a typedef enum for the bit masks (PIN0 through PIN3, PULLUP_LOW, PULLUP_HIGH)
Starts with register value 0x00 (all inputs, no pull-ups)
Sets PIN0 and PIN2 as outputs
Enables both pull-up bits
Toggles PIN1 direction
Clears PIN0 back to input
Prints the register state after each operation in binary and hex*/

#include <stdio.h>
#include <stdint.h>

typedef enum{
    PULLUP_PIN5 = 1<<5,
    PULLUP_PIN4 = 1<<4,
    PIN3 = 1<<3,
    PIN2 = 1<<2,
    PIN1 = 1<<1,
    PIN0 = 1
}bits;

void print_binary(uint8_t val) {
    for (int i = 7; i >= 0; i--)
        printf("%d", (val >> i) & 1);
    printf("\n");
}

int main(){

    uint8_t reg = 0x0;
    printf("Starts with register value: ");
    print_binary(reg);
    printf("Starts with register value: 0x%x\n\n", reg);

    reg |= PIN0; //Make Pin0 as 1
    printf("Sets PIN0 as outputs: ");
    print_binary(reg);
    printf("Sets PIN0 as outputs: 0x%x\n", reg);
    reg |= PIN1; //Make Pin0 as 1
    printf("Sets PIN1 as outputs: ");
    print_binary(reg);
    printf("Sets PIN1 as outputs: 0x%x\n\n", reg);

    reg |= PULLUP_PIN5; //Make Pin5 as 1
    printf("Enables PIN5 as pull-up: ");
    print_binary(reg);
    printf("Enables PIN5 as pull-up: 0x%x\n", reg);
    reg |= PULLUP_PIN4; //Make Pin4 as 1
    printf("Enables PIN4 as pull-up: ");
    print_binary(reg);
    printf("Enables PIN4 as pull-up: 0x%x\n\n", reg);

    reg ^= PIN1; //Toggles PIN1 direction
    printf("Toggles PIN1 direction: ");
    print_binary(reg);
    printf("Toggles PIN1 direction: 0x%x\n\n", reg);

    reg &= ~PIN0; //Clears PIN0 back to input
    printf("Clears PIN0 back to input: ");
    print_binary(reg);
    printf("Clears PIN0 back to input: 0x%x\n\n", reg);

    return 0;

}
