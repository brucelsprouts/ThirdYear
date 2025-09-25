#include <stdio.h>

int main () {
    int a, b, c, d, largest, smallest;
    
    printf("Enter four integers: ");
    scanf("%d %d %d %d", &a, &b, &c, &d);

    if (a > b) {
        largest = a;
        smallest = b;
    } else {
        largest = b;
        smallest = a;
    }
    
    int largestCD, smallestCD;
    if (c > d) {
        largestCD = c;
        smallestCD = d;
    } else {
        largestCD = d;
        smallestCD = c;
    }

    if (largestCD > largest) {
        largest = largestCD;
    }
    if (smallestCD < smallest) {
        smallest = smallestCD;
    }

    printf("Largest: %d\n", largest);
    printf("Smallest: %d\n", smallest);

    return 0;
}