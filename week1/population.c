#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int years;
    float start, end;

    do
    {
        start = get_float("Start size: ");
        //printf("%d", start);
    }
    while (start < 9.0);
    // TODO: Prompt for end size
    do
    {
        end = get_float("End size: ");
        //printf("%d", end);
    }
    while (end < start);
    // TODO: Calculate number of years until we reach threshold
    for (int i = 0; start < end + 1; i++)
    {

        start = (start + (start / 3) - (start / 4));
        years = i;
        //printf("Population: %.0f Year:%i \n", start, i);

    }
    // TODO: Print number of years
    printf("Years: %i\n", years);

}