#include <stdio.h>
#include <stdbool.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3
int canGrantRequest(int request[], int need[], int available[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[i]) {
            printf("Error: Request exceeds need.\n");
            return 0;
        }
        if (request[i] > available[i]) {
            printf("Error: Request exceeds available resources.\n");
            return 0;
        }
    }
    return 1;
}
int isSafe(int allocation[][MAX_RESOURCES], int max[][MAX_RESOURCES], int available[]) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safe_seq[MAX_PROCESSES];
    int count = 0;
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    while (count < MAX_PROCESSES) {
        bool allocated = false;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > available[j]) break;
                }
                if (j == MAX_RESOURCES) {
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    allocated = true;
                    for (j = 0; j < MAX_RESOURCES; j++) {
                        available[j] += allocation[i][j];
                    }
                }
            }
        }
        if (!allocated) {
            printf("System is in an unsafe state.\n");
            return 0;
        }
    }
    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("P%d ", safe_seq[i]);
    }
    printf("\n");
    return 1;
}
int main() {
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}
    };
    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {4, 2, 2}, {5, 3, 3}
    };
    int available[MAX_RESOURCES] = {3, 3, 2};
    int request[MAX_RESOURCES] = {1, 0, 2};
    int need[MAX_PROCESSES][MAX_RESOURCES];
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    if (canGrantRequest(request, need[0], available)) {
        int tempAvailable[MAX_RESOURCES];
        for (int i = 0; i < MAX_RESOURCES; i++) {
            tempAvailable[i] = available[i] - request[i];
        }
        if (isSafe(allocation, max, tempAvailable)) {
            printf("Request can be granted safely.\n");
        } else {
            printf("Request cannot be granted safely.\n");
        }
    }
    return 0;
}