/*Today's problem:
    Write a C program to check whether a given integer is a palindrome number.
*/

#include <stdio.h>

int main(){

    int a, q, rem, rev =0;
    printf("Enter a number: ");
    scanf("%d", &a);

    if (a<0)
        q = a * (-1);
    else
        q = a;

    while(q!=0){
        rem = q % 10;
        rev = (rev * 10) + rem;
        q = q / 10;
    }

    printf("Reverse: %d\n", rev);

    if(q ==  rev)
        printf("Number is palindrome");
    else
        printf("Number is not palindrome");

    return 0;
}

/*#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t x = 255;
    printf("uint8_t at 255:   %d\n", x);
    x++;
    printf("uint8_t after ++: %d\n", x);

    int8_t y = 127;
    printf("int8_t at 127:    %d\n", y);
    y++;
    printf("int8_t after ++:  %d\n", y);

    int a = -1;
    unsigned int b = 1;
    if (a < b)
        printf("a is less than b\n"); 
    else
        printf("b is less than a\n"); //this prints

    
    uint8_t len = 0;
    len = len-1;
    if (len > 10)
        printf("yes greater than 10, len =%d\n", len); //yes, len = 255;
    else
        printf("not greater, len =%d\n", len);

    return 0;
}*/