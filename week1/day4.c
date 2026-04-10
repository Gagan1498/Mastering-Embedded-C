#include <stdio.h>
#include <stdint.h>

int main(){
    
    /*Type-casting*/
    uint16_t adc_raw = 3000;  // 12-bit ADC reading (0–4095)
    float voltage = (float) adc_raw / 4095 * 3.3f; 
    float voltage2 = adc_raw/4095 * 3.3f; 

    printf("voltage = %f\n", voltage); //2.417583
    printf("voltage2 = %f\n", voltage2); //0.000000
    
    /*Operators*/
    // --- Operator Precedence ---
    int x = 2 + 3 * 4;
    int y = 10 - 4 - 2;
    int z = 1 << 2 + 1;  // trap: + has higher precedence than 
    int z_fixed = (1 << 2) + 1;  // explicit parens
    printf("=== Precedence ===\n");
    printf("x = %d\n", x);           // 14
    printf("y = %d\n", y);           // 4
    printf("z = %d\n", z);           // 8, not 3!
    printf("z_fixed = %d\n", z_fixed); // 5

    // --- Pre vs Post Increment ---
    int i = 5;
    int a = i++;   // here i++ means i=i+1; a gets 5, then i becomes 6
    int b = ++i;   // i becomes 7, then b gets 7
    printf("\n=== Pre/Post Increment ===\n");
    printf("a = %d\n", a);   // 5
    printf("b = %d\n", b);   // 7
    printf("i = %d\n", i);   // 7

    // --- Ternary ---
    int temp = 45;
    printf("\n=== Ternary ===\n");
    printf("%s\n", temp > 100 ? "critical" : temp > 50 ? "warning" : "normal"); // normal; : acts as else/if statement breaker

    // --- Logical vs Bitwise ---
    int p = 0;   // 0101
    int q = 3;   // 0011
    printf("\n=== Logical vs Bitwise ===\n");
    printf("p && q = %d\n", p && q);  // 1; logical operator: is q true (1 or greater) AND q is also true?
    printf("p & q  = %d\n", p & q);  // 1
    printf("p || q = %d\n", p || q); // 1; bitwise operator: bit by bit operation.
    printf("p | q  = %d\n", p | q);  // 7

    // --- The embedded trap ---
    uint8_t flags = 4;  // 00000100
    printf("\n=== Flags Trap ===\n");
    printf("flags & 2  = %d\n", flags & 2);   // 0 - bit 1 not set
    printf("flags && 2 = %d\n", flags && 2);  // 1 - logically true, WRONG intent

    // --- sizeof ---
    int arr[5];
    printf("\n=== sizeof ===\n");
    printf("sizeof(arr)               = %zu\n", sizeof(arr));           // 20
    printf("sizeof(arr)/sizeof(arr[0])= %zu\n", sizeof(arr)/sizeof(arr[0])); // 5

    return 0;
}