#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
volatile int running = 1; 
void handle_sigint(int sig) {
    printf("\nSignal %d received. Gracefully exiting...\n", sig);
    running = 0;
}
void *threadA(void *arg) {
    clock_t start = clock();

    int N = *(int *)arg;
    int sum = 0, count = 0, num = 2;

    while (count < N && running) {
        int isPrime = 1;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime) {
            sum += num;
            count++;
        }
        num++;
    }

    if (running)
        printf("Thread A: Sum of first %d primes is %d\n", N, sum);

    printf("Thread A Execution Time: %.4f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    pthread_exit(NULL);
}
void *threadB(void *arg) {
    clock_t start = clock();

    while (running) {
        printf("Thread B: Thread 1 running\n");
        sleep(2);
    }

    printf("Thread B Execution Time: %.4f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    pthread_exit(NULL);
}
void *threadC(void *arg) {
    clock_t start = clock();

    while (running) {
        printf("Thread C: Thread 2 running\n");
        sleep(3);
    }

    printf("Thread C Execution Time: %.4f seconds\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    pthread_exit(NULL);
}

int main() {
    signal(SIGINT, handle_sigint);
    clock_t start_compilation = clock();
    pthread_t tA, tB, tC;
    int N;

    printf("Enter value of N: ");
    scanf("%d", &N);
    pthread_create(&tA, NULL, threadA, &N);
    pthread_create(&tB, NULL, threadB, NULL);
    pthread_create(&tC, NULL, threadC, NULL);
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);

    printf("Compilation and Execution Time: %.4f seconds\n", (double)(clock() - start_compilation) / CLOCKS_PER_SEC);

    printf("All threads completed.\n");

    return 0;
}
