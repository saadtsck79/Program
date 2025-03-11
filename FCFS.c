#include<stdio.h>
int main() {
    int n;
    printf("Enter the number of process: ");
    scanf("%d", &n);
    int pid[n];
    int bt[n];
    int wt[n];
    int tat[n];
    printf("Enter process IDs:\n");
    for(int i=0; i<n; i++) {
        printf("Process %d: ", i+1);
        scanf("%d", &pid[i]);
    }
    printf("Enter burst times:\n");
    for(int i=0; i<n; i++) {
        printf("Burst time for process %d: ", pid[i]);
        scanf("%d", &bt[i]);
    }
    wt[0] = 0;
    for(int i=1; i<n; i++) {
        wt[i] = bt[i-1] + wt[i-1];
    }
    for(int i=0; i<n; i++) {
        tat[i] = bt[i] + wt[i];
    }
    printf("\nProcess\tBurst time\tWaiting time\tTurnaround time\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", pid[i], bt[i], wt[i], tat[i]);
    }
    float total_wt = 0, total_tat = 0;
    for(int i=0; i<n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("\nAverage waiting time: %2f\n", total_wt/n);
    printf("Average turnaround time: %2f\n", total_tat/n);
    return 0;
}