#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height, dots;
    do
    {
        //gets an input and copies to var dots
        height = get_int("Height: ");
        dots = height;
    }
    while (height < 0 || height == 0 || height > 8);


    for (int i = 1; i < height + 1; i++, dots--)
    {
        //prints empty spaces
        for (int k = 0; k < (dots - 1); k++)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        //prints a new line
        printf("\n");
    }
}




