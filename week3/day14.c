#include <stdio.h>

int add(int a, int b){
    return a+b;
}

int subtract(int a, int b){
    return a-b;
}

int multiply(int a, int b){
    return a*b;
}

void apply(int (*fp)(int, int), int a, int b){
    printf("%d\n", fp(a, b));
}

int main(){

    /*It takes a function pointer as a parameter and calls it with a and b, 
    printing the result.*/
    int (*ops[3])(int, int) = {add, subtract, multiply};

    apply(ops[0], 10, 5);
    apply(ops[1], 10, 5);
    apply(ops[2], 10, 5);

    /*Making an array of function pointers and calling thm in a loop*/
    #if 0
    int (*ops[3])(int, int) = {add, subtract, multiply};
    /* How to read: fp is an array of 3 pointers, each pointing to a 
    function that takes two ints and returns int.*/

    for(int i=0; i<3; i++){
        printf("%d\n", ops[i](10,5));
    }
    #endif

    /*Without making an array of function pointer */
    #if 0
    int (*fp1)(int, int) =  add;
    printf("add: %d\n", fp1(10, 5));

    int (*fp2)(int, int) = subtract;
    printf("subtract: %d\n", fp2(10, 5));
    
    int (*fp3)(int, int)  = multiply;
    printf("multiply: %d\n", fp3(10, 5));
    #endif

    return 0;

}