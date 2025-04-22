#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void firstFit(int n, int m, vector<int> frames, vector<int> processes) {
    cout << "\n--- First Fit ---\n";
    for (int i = 0; i < n; i++) {
        bool allocated = false;
        for (int j = 0; j < m; j++) {
            if (frames[j] >= processes[i]) {
                cout << "Process " << i + 1 << " allocated to frame " << j + 1 << endl;
                frames[j] -= processes[i];
                allocated = true;
                break;
            }
        }
        if (!allocated)
            cout << "Process " << i + 1 << " cannot be allocated\n";
    }
}

void bestFit(int n, int m, vector<int> frames, vector<int> processes) {
    cout << "\n--- Best Fit ---\n";
    for (int i = 0; i < n; i++) {
        int index = -1, smallest = INT_MAX;
        for (int j = 0; j < m; j++) { 
            if (frames[j] >= processes[i] && frames[j] < smallest) {
                smallest = frames[j];
                index = j;
            }
        }
        if (index == -1)
            cout << "Process " << i + 1 << " cannot be allocated\n";
        else {
            cout << "Process " << i + 1 << " allocated to frame " << index + 1 << endl;
            frames[index] -= processes[i];
        }
    }
}

void worstFit(int n, int m, vector<int> frames, vector<int> processes) {
    cout << "\n--- Worst Fit ---\n";
    for (int i = 0; i < n; i++) {
        int index = -1, largest = INT_MIN;
        for (int j = 0; j < m; j++) {
            if (frames[j] >= processes[i] && frames[j] > largest) {
                largest = frames[j];
                index = j;
            }
        }
        if (index == -1)
            cout << "Process " << i + 1 << " cannot be allocated\n";
        else {
            cout << "Process " << i + 1 << " allocated to frame " << index + 1 << endl;
            frames[index] -= processes[i];
        }
    }
}

void nextFit(int n, int m, vector<int> frames, vector<int> processes) {
    cout << "\n--- Next Fit ---\n";
    int index = 0;

    for (int i = 0; i < n; i++) {
        bool allocated = false;

        for (int count = 0; count < m; count++) {
            int j = (index + count) % m;

            if (frames[j] >= processes[i]) {
                cout << "Process " << i + 1 << " allocated to frame " << j + 1 << endl;
                frames[j] -= processes[i];
                index = j;  // Update index to the last allocated position
                allocated = true;
                break;
            }
        }

        if (!allocated)
            cout << "Process " << i + 1 << " cannot be allocated\n";
    }
}


int main() {
    int m, n;
    cout << "Enter number of memory blocks: ";
    cin >> m;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> frames(m), processes(n);
    cout << "Enter sizes of memory blocks:\n";
    for (int i = 0; i < m; i++) cin >> frames[i];

    cout << "Enter sizes of processes:\n";
    for (int i = 0; i < n; i++) cin >> processes[i];

    int choice;
    do {
        cout << "\n--- Memory Allocation Menu ---\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Next Fit\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: firstFit(n, m, frames, processes); break;
            case 2: bestFit(n, m, frames, processes); break;
            case 3: worstFit(n, m, frames, processes); break;
            case 4: nextFit(n, m, frames, processes); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
