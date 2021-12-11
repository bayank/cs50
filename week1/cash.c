#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int quarters, dimes, nickels, pennies, coins;
    float dollars, cents, cents_left;

    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    cents = round(dollars * 100);
    cents_left = cents;
    //printf("%.0f cents", cents);
    //printf("%.2f dollars ", dollars);

    for (quarters = 0; cents_left >= 25; quarters++)
    {
        cents_left = cents_left - 25;
    }
    //printf("%d quarters", quarters);
    //printf("%f cents left", cents_left);

    for (dimes = 0; cents_left >= 10; dimes++)
    {
        cents_left = cents_left - 10;
    }

    for (nickels = 0; cents_left >= 5; dimes++)
    {
        cents_left = cents_left - 5;
    }

    for (pennies = 0; cents_left >= 1; dimes++)
    {
        cents_left = cents_left - 1;
    }

    coins = quarters + dimes + nickels + pennies; // + nickels + pennies;
    printf("%d\n", coins);
    //printf("%d coins", coins);
    //printf("%f cents left", cents_left);

}