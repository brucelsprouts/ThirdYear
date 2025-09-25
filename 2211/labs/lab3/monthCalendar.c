#include <stdio.h>

int main() {
    int days, startDay;

    printf("Enter number of days in month: ");
    scanf("%d", &days);

    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    scanf("%d", &startDay);

    for (int i = 1; i < startDay; i++) {
        printf("   ");
    }

    for (int day = 1; day <= days; day++) {
        printf("%3d", day);

        if ((day + startDay - 1) % 7 == 0) {
            printf("\n");
        }
    }

    printf("\n");
    return 0;
}
