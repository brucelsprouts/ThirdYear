#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void simplify_fraction(int *numerator, int *denominator) {
    int common_divisor = gcd(*numerator, *denominator);
    *numerator /= common_divisor;
    *denominator /= common_divisor;
}

int main() {
    int num1, den1, num2, den2;

    printf("Enter two fractions separated by a plus sign (e.g., 5/6+3/4): ");
    scanf("%d/%d+%d/%d", &num1, &den1, &num2, &den2);

    int sum_num = num1 * den2 + num2 * den1;
    int sum_den = den1 * den2;

    printf("The sum is %d/%d\n", sum_num, sum_den);

    simplify_fraction(&sum_num, &sum_den);
    printf("The sum in simplest form is %d/%d\n", sum_num, sum_den);

    return 0;
}