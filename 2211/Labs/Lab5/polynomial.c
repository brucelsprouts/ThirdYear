#include <stdio.h>

long long power(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) {
        res *= base;
    }
    return res;
}

int main() {
    int x;
    printf("Enter a value for x: ");
    scanf("%d", &x);

    long long result = 3 * power(x, 5) + 2 * power(x, 4) - 5 * power(x, 3) - power(x, 2) + 7 * x - 6;

    printf("The value of the polynomial is: %lld\n", result);

    return 0;
}