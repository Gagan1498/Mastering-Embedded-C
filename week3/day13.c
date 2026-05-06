/*Write two functions:
cvoid scale_readings(int *data, int len, int factor);
void print_sensor(const int *data, int len);

scale_readings — multiplies every element by factor in place, 
using pointer arithmetic only

print_sensor — prints each value and its index, using pointer 
arithmetic only, must use const int * and must NOT modify any 
values*/

#include <stdio.h>

void scale_readings(int *data, int len, int factor){
    for (int i=0; i<len; i++){
        *(data + i) = *(data + i) * factor;
    }
}

void print_sensor(const int *data, int len){
    for(int i=0; i<len; i++){
        printf("index %d: %d\n", i, *(data + i));
    }
}

int main(){

    int sensors[5] = {100, 200, 300, 400, 500};
    scale_readings(sensors, 5, 2);
    print_sensor(sensors, 5);

    #if 0
    int a = 5, b = 10;
    const int *p = &a; //go from right to left to read this
    /*p is a pointer to an integer that is const*/
    *p = 20;   // line A - compile error
    p = &b;    // line B
    #endif
    
    #if 0
    int a = 5, b = 10;
    int * const p = &a;
    /*p is a const pointer to an integer*/
    *p = 20;   // line A
    p = &b;    // line B - compile error
    #endif

    #if 0
    int a = 5, b = 10;
    const int * const p = &a;
    /*p is a const pointer to an integer which is const*/
    *p = 20;   // line A - compile error
    p = &b;    // line B - compile error
    #endif

    return 0;
}