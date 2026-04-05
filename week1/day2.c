#include <stdio.h>
#include <stdint.h>

int main(){
    printf("%zu\n", sizeof(int));
    printf("%zu\n", sizeof(char));
    printf("%zu\n", sizeof(float));
    printf("%zu\n", sizeof(double));
    printf("%zu\n", sizeof(uint8_t));
    printf("%zu\n", sizeof(uint16_t));
    printf("%zu\n", sizeof(uint32_t));

    /*Write a program that figures out the range of int8_t and uint8_t without using any library constants, just using sizeof() and math*/
    printf("%zu\n", sizeof(uint8_t));
    uint8_t max_uint8_t=0;
    for (int i=0;i<8;i++){
        int pow = 1<<i;
        max_uint8_t = max_uint8_t + pow;
    }
    printf("max for uint8_t = %d\n", max_uint8_t);

    printf("%zu\n", sizeof(int8_t));
    int8_t max_int8_t = 0, min_int8_t = 0;
    for (int i=0;i<7;i++){
        int pow = 1<<i;
        max_int8_t = max_int8_t + pow;
    }
    min_int8_t = -(1<<7); 
    
    printf("max for int8_t = %d\n", max_int8_t);
    printf("min for int8_t = %d", min_int8_t);

    return 0;
}