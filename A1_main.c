#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int choice;

    printf("You are in the Parent Process\n");
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());

    do {
        printf("\nMenu:\n");
        printf("1. GREP Command\n");
        printf("2. CP Command\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2) {
            pid_t pid = fork();

            if (pid == 0) {
                // Child process
                printf("You are in the Child Process\n");
                printf("PID: %d\n", getpid());
                printf("PPID: %d\n", getppid());

                if (choice == 1) {
                    char pattern[100], file[100];
                    printf("Enter filename: ");
                    scanf("%s", file);
                    printf("Enter pattern: ");
                    scanf("%s", pattern);
                    execlp("./mygrep", "mygrep", pattern, file, NULL);
                } else if (choice == 2) {
                    char src[100], dest[100];
                    printf("Enter source filename: ");
                    scanf("%s", src);
                    printf("Enter destination filename: ");
                    scanf("%s", dest);
                    execlp("./mycp", "mycp", src, dest, NULL);
                }

                perror("execlp failed");
                exit(1);
            } else if (pid > 0) {
                wait(NULL); // Wait for child
            } else {
                perror("Fork failed");
            }

        } else if (choice == 3) {
            printf("Thank you!\n");
        } else {
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);

    return 0;
}
