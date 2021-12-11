#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n = 0, y = 0;
    int *arr = (int*)malloc(n * sizeof(int));
    printf("How many numbers do you want to add?: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter number # %d: ", i);
        scanf("%d", &arr[i]);
        y = arr[i] + y;
    }


    for (int i = 0; i < n; i++)
    {
        //printf("Enter a number # %d: ", i);
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    //printf("arr = ")
    printf("sum of every element in the array is: %d", y);
    free(arr);
    return 0;
}