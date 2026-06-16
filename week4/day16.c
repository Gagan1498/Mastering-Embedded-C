#include <stdio.h>

int my_strlen(const char *s){
    int count = 0;
    while(*s != '\0'){
    count ++;
    *s++;
    }
    return count;
}

int main(){
    char arr[] = "hello world";
    int count = my_strlen(&arr[0]); //or simply use arr
    printf("length = %d\n", count);
    return 0;
}