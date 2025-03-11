#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3
bool canAllocate(int process, int need[MAX_PROCESSES][MAX_RESOURCES], int available[MAX_RESOURCES]) {
    for (int j = 0; j < MAX_RESOURCES; j++) {
        if (need[process][j] > available[j]) {
            return false;
        }
    }
    return true;
}
void allocateResources(int process, int alloc[MAX_PROCESSES][MAX_RESOURCES], 
                       int need[MAX_PROCESSES][MAX_RESOURCES], 
                       int available[MAX_RESOURCES], bool finished[MAX_PROCESSES]) {
    for (int j = 0; j < MAX_RESOURCES; j++) {
        available[j] += alloc[process][j];
    }
    finished[process] = true;
}
int main() {
    int n = MAX_PROCESSES;
    int m = MAX_RESOURCES; 
    int alloc[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}
    }; 
    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}
    }; 
    int available[MAX_RESOURCES] = {3, 3, 2};
    int need[MAX_PROCESSES][MAX_RESOURCES];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    bool finished[MAX_PROCESSES] = {false};
    int safe_seq[MAX_PROCESSES];
    int seq_index = 0;
    while (seq_index < n) {
        bool allocated = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i] && canAllocate(i, need, available)) {
                allocateResources(i, alloc, need, available, finished);
                safe_seq[seq_index++] = i;
                allocated = true;
                printf("Process P%d allocated resources\n", i);
            }
        }
        if (!allocated) {
            break;
        }
    }
    if (seq_index != n) {
        printf("Deadlock detected\n");
    } else {
        printf("Safe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safe_seq[i]);
        }
        printf("\n");
    }
    return 0;
}