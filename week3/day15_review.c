/******************************************************************************

You have a 16-bit sensor register. Bits 0-2 are a status field, bits 4-7 are a data field.
Write a complete program that:

Initializes the register to 0x0000
Sets bits 4-7 to value 0b1010 using your update_reg function
Reads back bits 4-7 using a separate read_field function that takes reg, pos, width and returns the value
Prints the result

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>

void update_reg(uint16_t *reg, int val, int pos, int width)
{
*reg &= ~ (((1 << width) - 1) << pos);
 *reg |= (val << pos);
}

int read_field(const uint16_t *reg, int pos, int width){
    int value = *reg;
    value &= (((1 << width) -1) << pos);
    value = value >> pos;
    return value;
}

int main() {
uint16_t reg = 0x0;
uint16_t *p = &reg;
update_reg(p,10,4,4);
int value = read_field(p, 4,4);
printf("%d", value);
return 0;
}