/*## Day 1 Mini Exercise

```c
int arr[5] = {10, 20, 30, 40, 50};
```

Write a function:
```c
void print_array(int *p, int len);
```

Rules:
- Traverse using **pointer arithmetic only** — no `arr[i]` index syntax inside the function
- Print each value and its address
- Call it from `main` using array decay*/

#include<stdio.h>

void print_array(int *p, int len){
    for (int i=0; i<len; i++)
        printf("%d at address 0x%p\n", *(p+i), (void *)(p+i));
}

int main(){

    /*int a = 5;
    int *pt = &a;
    printf("%d    ", *pt);
    printf("0x%x    \n", pt);*/

    int arr[5] = {10,20,30,40,50};
    int *p = arr; //same as &arr[0]
    
    print_array(arr, sizeof(arr)/sizeof(int));

    return 0;
}

