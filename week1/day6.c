/*
Write a program with and without using typedef that:

Starts with reg = 0b10100011
Set the data ready bit (bit 4)
Clear the overflow flag (bit 7)
Toggle the error flag (bit 6)
Check if busy flag (bit 1) is set and print "Device busy" or "Device free"
Print the register value after each operation
*/

/* With using typedef */
#include <stdio.h>
#include <stdint.h>

typedef enum {
    OVERFLOW =  7, //unlike struct no semicolon, only comma
    ERROR    =  6,
    DATA_RDY =  4,
    BUSY     =  1,
    ENABLE   =  0 //unlike struct, nothing here, no comma/semicolon
} Regbits; //Like struct, semicolon here

int main(){

    uint8_t reg = 0b10100011;
    printf("Reg value: %b\n", reg);

    reg = reg | (1 << DATA_RDY);
    printf("Set the data bit ready: %b\n", reg);

    reg = reg & ~(1 << OVERFLOW);
    printf("Clear the data overflow flag: %b\n", reg);

    reg = reg ^ (1 << ERROR);
    printf("Toggle the error flag: %b\n", reg);

    printf("Check if busy flag (bit 1) is set and print Device busy or Device free: \n");
    if (reg & (1 << BUSY)) {
        printf("Device busy!\n");
    }
    else {
    printf("Device is free!\n");
    }

    return 0;
}

/* Could have been used like this*/
/*Now RegBits is actually doing something — it's the type of the parameter. If you accidentally pass a wrong value like a Direction enum, the compiler can warn you.
This is also much cleaner code — the operations are reusable functions instead of repeated inline expressions. This is closer to how real embedded codebases look.*/
/*
#include <stdio.h>
#include <stdint.h>

typedef enum {
    OVERFLOW = 7,
    ERROR    = 6,
    DATA_RDY = 4,
    BUSY     = 1,
    ENABLE   = 0
} RegBits;

void set_bit(uint8_t *reg, RegBits bit) {  // ← RegBits used as parameter type
    *reg |= (1 << bit);
}

void clear_bit(uint8_t *reg, RegBits bit) {
    *reg &= ~(1 << bit);
}

void toggle_bit(uint8_t *reg, RegBits bit) {
    *reg ^= (1 << bit);
}

int main() {
    uint8_t reg = 0b10100011;

    set_bit(&reg, DATA_RDY);    // ← passing enum value
    clear_bit(&reg, OVERFLOW);
    toggle_bit(&reg, ERROR);

    if (reg & (1 << BUSY))
        printf("Device busy!\n");
    else
        printf("Device free!\n");

    return 0;
}
*/


/* Without using typedef */
/*
#define OVERFLOW  7
#define ERROR     6
#define DATA_RDY  4
#define BUSY      1
#define ENABLE    0

#include <stdio.h>
#include <stdint.h>

int main(){

    uint8_t reg = 0b10100011;
    printf("Reg value: %b\n", reg);

    reg = reg | (1 << DATA_RDY);
    printf("Set the data bit ready: %b\n", reg);

    reg = reg & ~(1 << OVERFLOW);
    printf("Clear the data overflow flag: %b\n", reg);

    reg = reg ^ (1 << ERROR);
    printf("Toggle the error flag: %b\n", reg);

    printf("Check if busy flag (bit 1) is set and print Device busy or Device free: \n");
    if (reg & (1 << BUSY)) {
        printf("Device busy!\n");
    }
    else {
    printf("Device is free!\n");
    }

    return 0;
}
*/