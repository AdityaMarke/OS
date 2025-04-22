#include <stdio.h>
#include <stdbool.h>

#define MAX 100

// Function to check if page is in memory
bool isInMemory(int memory[], int page, int capacity) {
    for (int i = 0; i < capacity; i++) {
        if (memory[i] == page)
            return true;
    }
    return false;
}

// FCFS Algorithm
int fcfs(int pages[], int n, int capacity) {
    int memory[capacity];
    int page_faults = 0, index = 0;

    for (int i = 0; i < capacity; i++) 
    memory[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!isInMemory(memory, pages[i], capacity)) {
            memory[index] = pages[i];
            index = (index + 1) % capacity;
            page_faults++;
        }
    }
    return page_faults;
}

// LRU Algorithm
int lru(int pages[], int n, int capacity) {
    int memory[capacity], time[MAX], counter = 0, page_faults = 0;

    for (int i = 0; i < capacity; i++) 
    memory[i] = -1;

    for (int i = 0; i < n; i++) {
        bool found = false;

        for (int j = 0; j < capacity; j++) {
            if (memory[j] == pages[i]) {
                time[j] = counter++;
                found = true;
                break;
            }
        }

        if (!found) {
            int lru_index = 0;
            for (int j = 1; j < capacity; j++) {
                if (time[j] < time[lru_index]) {
                    lru_index = j;
                }
            }
            memory[lru_index] = pages[i];
            time[lru_index] = counter++;
            page_faults++;
        }
    }
    return page_faults;
}

// Optimal Algorithm
int optimal(int pages[], int n, int capacity) {
    int memory[capacity], page_faults = 0;

    for (int i = 0; i < capacity; i++) 
    memory[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!isInMemory(memory, pages[i], capacity)) {
            int replace_index = -1, farthest = i + 1;

            for (int j = 0; j < capacity; j++) {
                for (int k = i + 1; k < n; k++) {
                    if (memory[j] == pages[k])
                        break;
                }

                if (k == n) {
                    replace_index = j;
                    break;
                } else if (k > farthest) {
                    farthest = k;
                    replace_index = j;
                } else if (replace_index == -1) {
                    replace_index = j;
                }
            }

            memory[replace_index] = pages[i];
            page_faults++;
        }
    }
    return page_faults;
}

int main() {
    int pages[MAX], n, capacity, choice;

    // Taking user input
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    // Menu for algorithm selection
    printf("\nChoose the page replacement algorithm to use:\n");
    printf("1. FCFS \n");
    printf("2. LRU \n");
    printf("3. Optimal \n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    // Switch-case structure to execute chosen algorithm
    switch (choice) {
        case 1:
            printf("\nFCFS Page Faults   : %d\n", fcfs(pages, n, capacity));
            break;
        case 2:
            printf("\nLRU Page Faults    : %d\n", lru(pages, n, capacity));
            break;
        case 3:
            printf("\nOptimal Page Faults: %d\n", optimal(pages, n, capacity));
            break;
        default:
            printf("Invalid choice. Please enter a valid option (1-3).\n");
            break;
    }

    return 0;
}
