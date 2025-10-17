#include <stdio.h>

int main() {
    int number;
    printf("Enter a three-digit number: ");
    scanf("%d", &number);

    int digit1 = number / 100;
    int digit2 = (number / 10) % 10;
    int digit3 = number % 10;

    int reversed_number = digit3 * 100 + digit2 * 10 + digit1;

    printf("The reversal is: %d\n", reversed_number);

    return 0;
}