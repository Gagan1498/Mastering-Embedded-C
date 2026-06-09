/* Week 3 project 
## Sensor Command Dispatcher

You're writing firmware for a device with 3 sensors — temperature, pressure, humidity. Each sensor has a 16-bit register.

Build a program that:

1. Stores 3 sensor registers as a `uint16_t` array
2. Has 3 functions — `read_sensor`, `write_sensor`, `reset_sensor` — each takes a `uint16_t *` and does something to the register
3. Stores those 3 functions in a **dispatch table** — array of function pointers
4. Has a `process` function that takes a `const uint16_t *` register and prints the value — read only, no modification
5. update_reg — takes a pointer to a 16-bit register, a value, a bit position, and a width. Writes the value into those specific bits without touching any other bits.
6. read_field — takes a pointer to a 16-bit register, a bit position, and a width. Extracts and returns the value stored in those bits.

**Constraints:**
- No hardcoded masks — everything dynamic
- `process` must use `const`
- Traverse the sensor array using pointer arithmetic only, no `arr[i]` in loops
*/

#include<stdio.h>
#include<stdint.h>

void read_sensor(uint16_t * reg_arr); //reads bits 0-3 using read_field and prints the value
void write_sensor(uint16_t * reg_arr); //writes value 0b1010 into bits 0-3 using update_reg
void reset_sensor(uint16_t * reg_arr); //sets the entire register to 0
void process(const uint16_t * reg_arr);
void update_reg(uint16_t * reg, uint16_t value, int pos, int width);
uint16_t read_field(uint16_t * reg, int pos, int width);

void process(const uint16_t * reg_arr){
    uint16_t value = *reg_arr;
    printf("0x%x", value);
}

void write_sensor(uint16_t * reg_arr){
    update_reg(reg_arr, 0xa, 0, 4);
}

void reset_sensor(uint16_t * reg_arr){
    *reg_arr = 0;
}

void read_sensor(uint16_t * reg_arr){
    uint16_t value;
    value = read_field(reg_arr, 0, 4);
    printf ("value = %d\n", value);
}

void update_reg(uint16_t * reg, uint16_t value, int pos, int width){
    *reg &= ~(((1<<(width)) - 1) << pos); //Precedence (high to low): () > ~ ! > * / % > + - > << >> > & > ^ > |
    *reg |= (value << pos);
}

uint16_t read_field(uint16_t * reg, int pos, int width){
    uint16_t val = 0;
    val = *reg & (((1<<(width)) - 1) << pos);
    val = val >> pos;
    return val;
}

int main(){

    uint16_t sensor_reg[3] = {0};
    void (*functpointer[3])(uint16_t * func) = {write_sensor, read_sensor, reset_sensor};
    
    for(int i=0;i<3;i++){
        for(int j=0; j<3;j++){
            functpointer[j](sensor_reg + i);
        }
    }

    return 0;
}