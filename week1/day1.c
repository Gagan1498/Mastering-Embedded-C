/*
int a = 5;
int b = 10;
```

After the swap, `a` should be 10 and `b` should be 5.

**Rules:**
- You must write a separate `swap()` function — don't do it inside main
- The function must take pointers as arguments, not the values directly
- Print the values of `a` and `b` before and after the swap to prove it worked

**Expected output:**
```
before swap: a = 5, b = 10
after swap:  a = 10, b = 5
*/

#include <stdio.h> //"file.c" for own header files, <> for standard C files

void swap(int *p_a, int *p_b){
    /*Approach 1: using a third variable*/
    /*int temp = *p_a;
    *p_a = *p_b;
    *p_b = temp;*/

    /*Approach 2: Without using a third variable*/
    /*this might overflow in a corner case*/
    /*p_a = *p_a + *p_b; 
    *p_b = *p_a - *p_b;
    *p_a = *p_a - *p_b;*/

    /*Approach 3: XOR*/
    /*XOR rule — simple:

    Same bits → gives 0
    Different bits → gives 1

    0 XOR 0 = 0
    1 XOR 1 = 0
    0 XOR 1 = 1
    1 XOR 0 = 1
    
    One magic property of XOR:
    a XOR a = 0        // anything XORed with itself = 0
    a XOR 0 = a        // anything XORed with 0 = itself
    a XOR b XOR b = a  // XOR twice cancels out
    
    The third property is magical and applied below*/

    *p_a = *p_a ^ *p_b; 
    *p_b = *p_a ^ *p_b;
    *p_a = *p_a ^ *p_b;

}

int main(){
    int a = 5;
    int b = 10;

    printf("before swap: a = %d, b = %d\n", a,b);
    swap(&a, &b);
    printf("after swap: a = %d, b = %d\n", a,b);

    return 0;
}


