#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DISK_SIZE 200 // Default disk size

void fifo(int requests[], int n, int head)
{
    int total = 0;
    printf("\nFIFO Order: %d", head);
    for (int i = 0; i < n; i++)
    {
        total += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time (FIFO): %d\n", total);
}

void sstf(int requests[], int n, int head) {
    int total = 0, completed = 0;
    int visited[n];

    // Initialize all requests as unvisited
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nSSTF Order: %d", head);

    while (completed < n) {
        int closest = -1, min_dist = __INT_MAX__;

        // Find the nearest unvisited request
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int distance = abs(requests[i] - head);
                if (distance < min_dist) {
                    min_dist = distance;
                    closest = i;
                }
            }
        }

        // Move head to the closest request
        visited[closest] = 1;
        total += min_dist;
        head = requests[closest];
        printf(" -> %d", head);
        completed++;
    }

    printf("\nTotal Seek Time (SSTF): %d\n", total);
}

void scan(int requests[], int n, int head) {
    int total = 0;
    int i;

    // Sort the requests in ascending order
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Find index where head fits into the sorted array
    int pos = 0;
    while (pos < n && requests[pos] < head)
        pos++;

    printf("\nSCAN Order: %d", head);

    // Move right (towards higher-numbered tracks)
    for (i = pos; i < n; i++) {
        printf(" -> %d", requests[i]);
        total += abs(head - requests[i]);
        head = requests[i];
    }

    // Move left (towards lower-numbered tracks)
    for (i = pos - 1; i >= 0; i--) {
        printf(" -> %d", requests[i]);
        total += abs(head - requests[i]);
        head = requests[i];
    }

    printf("\nTotal Seek Time (SCAN): %d\n", total);
}

void cscan(int requests[], int n, int head) {
    int total = 0;
    int i;

    // Sort the requests in ascending order
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Find the index where the head fits in the sorted array
    int pos = 0;
    while (pos < n && requests[pos] < head)
        pos++;

    printf("\nC-SCAN Order: %d", head);

    // Move right from head to the end
    for (i = pos; i < n; i++) {
        printf(" -> %d", requests[i]);
        total += abs(head - requests[i]);
        head = requests[i];
    }

    // Simulate circular jump to the beginning
    if (pos > 0) {
        total += abs(head - (DISK_SIZE - 1));  // Move to end
        total += DISK_SIZE - 1;                // Wrap around to start

        head = 0;
        printf(" -> 0");

        // Continue from beginning to the left side
        for (i = 0; i < pos; i++) {
            printf(" -> %d", requests[i]);
            total += abs(head - requests[i]);
            head = requests[i];
        }
    }

    printf("\nTotal Seek Time (C-SCAN): %d\n", total);
}

int main()
{
    int n, head, choice;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    int requests[n];

    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("\n--- Disk Scheduling Menu ---\n");
    printf("1. FIFO\n");
    printf("2. SSTF\n");
    printf("3. SCAN\n");
    printf("4. C-SCAN\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        fifo(requests, n, head);
        break;
    case 2:
        sstf(requests, n, head);
        break;
    case 3:
        scan(requests, n, head);
        break;
    case 4:
        cscan(requests, n, head);
        break;
    default:
        printf("Invalid choice!\n");
    }

    return 0;
}
