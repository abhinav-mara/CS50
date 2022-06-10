#include <stdio.h>
#include <cs50.h>

int get_cents();
int calculate_quarters(int c);
int calculate_dimes(int c);
int calculate_nickels(int c);
int calculate_pennies(int c);

int main(void) 
{
    int cents = get_cents();
    int totalCoins = 0;
    totalCoins += calculate_quarters(cents);
    cents -= calculate_quarters(cents) * 25;
    totalCoins += calculate_dimes(cents);
    cents -= calculate_dimes(cents) * 10;
    totalCoins += calculate_nickels(cents);
    cents -= calculate_nickels(cents) * 5;
    totalCoins += calculate_pennies(cents);
    printf("%i\n", totalCoins);
}