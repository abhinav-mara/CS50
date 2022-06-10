#include <cs50.h>

int get_cents() {
    int cents;
    do {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);
    return cents;
}

int calculate_quarters(int c) {
    return c/25;
}

int calculate_dimes(int c) {
    return c/10;
}

int calculate_nickels(int c) {
    return c/5;
}

int calculate_pennies(int c) {
    return c;
}