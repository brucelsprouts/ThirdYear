#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i = i + 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    return 1;
}

void calculate_primes_in_range(int min_range, int max_range, int parent_pid, int original_max) {
    int count = 0;
    long long sum = 0;
    for (int i = min_range; i <= max_range; i++) {
        if (is_prime(i)) {
            count++;
            sum += i;
        }
    }
    int display_upper_bound;
    if (max_range == original_max) {
        display_upper_bound = max_range;
    } else {
        display_upper_bound = max_range + 1;
    }
    printf("pid: %d, ppid %d - Count and sum of prime numbers between %d and %d are %d and %lld\n",
           getpid(), parent_pid, min_range, display_upper_bound, count, sum);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <0_serial_1_parallel> <min> <max>\n", argv[0]);
        return 1;
    }

    int mode = atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    if (min == 0 && argv[2][0] != '0') {
        fprintf(stderr, "Error: Minimum value must be an integer.\n");
        return 1;
    }
    if (max == 0 && argv[3][0] != '0') {
        fprintf(stderr, "Error: Maximum value must be an integer.\n");
        return 1;
    }
    if (max < min) {
        fprintf(stderr, "Error: Maximum value must be greater than or equal to minimum value.\n");
        return 1;
    }
    
    printf("Process id: %d\n", getpid());

    int ranges[4][2];
    int range_size = (max - min + 1) / 4;
    
    for (int i = 0; i < 4; i++) {
        ranges[i][0] = min + i * range_size;
        ranges[i][1] = min + (i + 1) * range_size - 1;
    }
    ranges[3][1] = max;

    if (mode == 0) {
        for (int i = 0; i < 4; i++) {
            calculate_primes_in_range(ranges[i][0], ranges[i][1], getppid(), max);
        }
    } else {
        pid_t pids[4];
        for (int i = 0; i < 4; i++) {
            pids[i] = fork();

            if (pids[i] < 0) {
                perror("fork failed");
                return 1;
            } else if (pids[i] == 0) {
                calculate_primes_in_range(ranges[i][0], ranges[i][1], getppid(), max);
                exit(0);
            }           
        }

        for (int i = 0; i < 4; i++) {
            wait(NULL);
        }
    }

    return 0;
}