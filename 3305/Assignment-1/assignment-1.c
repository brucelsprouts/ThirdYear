#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to check if a number is prime
int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i = i + 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    return 1;
}

// Function to calculate primes in a given range and print output
void calculate_primes_in_range(int min_range, int max_range, int parent_pid) {
    int count = 0;
    long long sum = 0;
    for (int i = min_range; i <= max_range; i++) {
        if (is_prime(i)) {
            count++;
            sum += i;
        }
    }
    printf("pid: %d, ppid %d - Count and sum of prime numbers between %d and %d are %d and %lld\n",
           getpid(), parent_pid, min_range, max_range, count, sum);
}

int main(int argc, char *argv[]) {
    // Validate command-line arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <0_serial_1_parallel> <min> <max>\n", argv[0]);
        return 1;
    }

    int mode = atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    // Validate argument types and range
    if (min == 0 && argv[2][0] != '0') { // Check for non-integer min
        fprintf(stderr, "Error: Minimum value must be an integer.\n");
        return 1;
    }
    if (max == 0 && argv[3][0] != '0') { // Check for non-integer max
        fprintf(stderr, "Error: Maximum value must be an integer.\n");
        return 1;
    }
    if (max < min) {
        fprintf(stderr, "Error: Maximum value must be greater than or equal to minimum value.\n");
        return 1;
    }
    
    // Print parent process ID
    printf("Process id: %d\n", getpid());

    int ranges[4][2];
    int range_size = (max - min + 1) / 4;
    
    for (int i = 0; i < 4; i++) {
        ranges[i][0] = min + i * range_size;
        ranges[i][1] = min + (i + 1) * range_size - 1;
    }
    ranges[3][1] = max; // Ensure the last range goes up to max

    if (mode == 0) { // Serial mode
        for (int i = 0; i < 4; i++) {
            calculate_primes_in_range(ranges[i][0], ranges[i][1], getppid());
        }
    } else { // Parallel mode
        pid_t pids[4];
        for (int i = 0; i < 4; i++) {
            pids[i] = fork();

            if (pids[i] < 0) {
                perror("fork failed");
                return 1;
            } else if (pids[i] == 0) { // Child process
                calculate_primes_in_range(ranges[i][0], ranges[i][1], getppid());
                exit(0); // Child exits after calculation
            }           
        }

        // Parent waits for all children
        for (int i = 0; i < 4; i++) {
            wait(NULL);
        }
    }

    return 0;
}
