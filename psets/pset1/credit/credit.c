#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // SET CONST IN ORDER TO ACCESS VARIABLE MULTIPLE TIMES (AND BECAUSE WE KNOW THIS VALUE SHOULD NOT BE CHANGED)
    const long NUMBER = get_long("Enter credit card number: ");

    // DETERMINE THE SUM OF DOUBLE THE VALUE OF EVERY OTHER DIGIT STARTING FROM SECOND TO LAST
    long first = NUMBER;
    first /= 10;                            // offset by 1 digit in order to account for second to last aspect
    int firstSum = 0;
    while (first > 0) {
        int remainder = first % 100;        // determine the digit by taking the remainder out of 100, and again out of 10 if required
        if (remainder > 9) {
            remainder %= 10;
        }
        remainder *= 2;                     // multiply by 2 to acquire new number
        while (remainder > 0) {             // add the digits of the previously determined new number
            firstSum += remainder % 10;
            remainder /= 10;
        }
        first /= 100;                       // increment by /= 100 in order to account for every other digit in cc number
    }

    printf("First Sum:%i\n", firstSum);

    // DETERMINE THE SUM OF EVERY VALUE THAT WAS NOT USED IN THE PREVIOUS RUN
    long second = NUMBER;
    int secondSum = 0;
    while (second > 0) {                    // same thing as first run but without doubling the digits
        int remainder = second % 100;
        if (remainder > 9) {
            remainder %= 10;
        }
        while (remainder > 0) {
            secondSum += remainder % 10;
            remainder /= 10;
        }

        second /= 100;
    }

    printf("Second Sum: %i\n", secondSum);

    int totalSum = firstSum + secondSum;

    printf("Total: %i\n", totalSum);                    // calculate the total sum for later use

    
    // DETERMINE FIRST TWO DIGITS
    long firstTwo = NUMBER;

    if (firstTwo % 2 == 0) {                            // because we need first two digits, its necessary to decrement by /= 100,
        while (firstTwo > 100) {                        // but an odd number of digits will mess this up...
            firstTwo /= 100;
        }
        printf("First 2 digits: %li\n", firstTwo);
    }
    else {
        while (firstTwo > 100) {                        // therefore, parity is check and odd numbers are given an additional operation
            if (firstTwo > 100 && firstTwo < 999) {     // in order to acquire first 2 digits
                firstTwo /= 10;
            }
            else {
                firstTwo /= 100;
            }

        }
        printf("First 2 digits: %li\n", firstTwo);
    }

    // DETERMINE NUMBER OF DIGITS
    long fourth = NUMBER;
    int numDigits = 0;

    while (fourth > 0) {
        fourth /= 10;
        numDigits++;
    }
    printf("Number of digits: %i\n", numDigits);

    /* 
    Number of Digits
    American Express - 15
    MasterCard - 16
    VISA - 13,16
    Start of Number
    American Express - 34,37
    MasterCard - 51,52,53,54,55
    VISA - 4
    */

   // CONDITIONALS FOR OUTPUT
   if ((totalSum % 10 == 0) && numDigits == 15 && (firstTwo == 34 || firstTwo == 37)) {
       printf("American Expres\n");
   }
   else if ((totalSum % 10 == 0) && numDigits == 16 && (firstTwo == 51 || firstTwo == 52 || firstTwo == 53 || 
                                                        firstTwo == 54 || firstTwo == 55)) {
                                                            printf("MasterCard\n");
                                                        }
    else if ((totalSum % 10 == 0) && (numDigits == 13 || numDigits == 16) && (firstTwo / 10 == 4)) {
        printf("VISA\n");
    }
    else {
        printf("INVALID\n");
    }
}