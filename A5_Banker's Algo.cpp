#include <iostream>
using namespace std;

const int MAX_PROCESSES = 10;
const int MAX_RESOURCES = 10;

// Number of processes and resources (to be input by user)
int n, m;

// Available resources of each type
int available[MAX_RESOURCES];

// Maximum demand of each process
int maximum[MAX_PROCESSES][MAX_RESOURCES];

// Currently allocated resources to each process
int allocation[MAX_PROCESSES][MAX_RESOURCES];

// Remaining need of each process = maximum - allocation
int need[MAX_PROCESSES][MAX_RESOURCES];

// Function to input system state from user
void inputData() {
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    // Input available instances for each resource type
    cout << "\nEnter available resources:\n";
    for (int i = 0; i < m; i++) {
        cout << "Resource R" << i + 1 << ": ";
        cin >> available[i];
    }

    // Input maximum demand matrix
    cout << "\nEnter maximum resources for each process (row-wise):\n";
    for (int i = 0; i < n; i++) {
        cout << "Process P" << i << ": ";
        for (int j = 0; j < m; j++) {
            cin >> maximum[i][j];
        }
    }

    // Input allocation matrix and calculate the need matrix
    cout << "\nEnter allocated resources for each process (row-wise):\n";
    for (int i = 0; i < n; i++) {
        cout << "Process P" << i << ": ";
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
            // Need = Maximum - Allocation
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// Function to check whether the system is in a safe state
void isSafe() {
    // Finish array keeps track of processes that are done
    bool finish[MAX_PROCESSES] = {false};

    // Work array represents available resources for each step
    int work[MAX_RESOURCES];

    // To store the safe sequence of processes
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    // Initialize work = available
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    // Try to find a safe sequence
    while (count < n) {
        bool found = false;

        // Loop through all processes to find a valid one
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true;

                // Check if this process can be executed with available resources
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                // If it can be executed, simulate it
                if (possible) {
                    // After execution, its allocated resources are released
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    // Add this process to the safe sequence
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        // If no process could be executed in this round, deadlock is possible
        if (!found) {
            cout << "\nSystem is in an **unsafe state**. Deadlock may occur.\n";
            return;
        }
    }

    // If all processes can finish, it's a safe state
    cout << "\nSystem is in a **safe state**.\nSafe sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSequence[i];
        if (i != n - 1) cout << " -> ";
    }
    cout << endl;
}

// Main function
int main() {
    inputData();  // Step 1: Get system data from user
    isSafe();     // Step 2: Run Banker's Algorithm to check safety
    return 0;
}
