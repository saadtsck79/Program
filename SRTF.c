#include<stdio.h>
struct Process {
    int id;
    int at;
    int bt;
    int rt;
    int ct;
    int wt;
    int tat;
};
void find_srtf(struct Process processes[], int n) {
    int time = 0;
    int completed = 0;
    int min_index;
    float total_wt = 0, total_tat = 0;
    while(completed < n) {
        min_index = -1;
        for(int i=0; i<n; i++) {
            if(processes[i].at <= time && processes[i].rt > 0) {
                if(min_index == -1 || processes[i].rt < processes[min_index].rt) {
                    min_index = i;
                }
            }
        }
        if(min_index != -1) {
            processes[min_index].rt--;
            if(processes[min_index].rt == 0) {
                completed++;
                processes[min_index].ct = time + 1;
                processes[min_index].tat = processes[min_index].ct - processes[min_index].at;
                processes[min_index].wt = processes[min_index].tat - processes[min_index].bt;
                total_wt += processes[min_index].wt;
                total_tat += processes[min_index].tat;
            }
        }
        time++;
    }
    printf("\nProcess ID\tArrival time\tBurst time\tCompletion time\tWaiting time\tTurnaround time\n");
    for(int i=0; i<n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].at, processes[i].bt, processes[i].ct, processes[i].wt, processes[i].tat);
    }
    printf("\nAverage waiting time: %2f", total_wt/n);
    printf("Average turnaround time: %2f", total_tat/n);
}
int main() {
    int n;
    printf("Enter number of process: ");
    scanf("%d", &n);
    struct Process processes[n];
    for(int i=0; i<n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d%d", &processes[i].at, &processes[i].bt);
        processes[i].rt = processes[i].bt;
    }
    find_srtf(processes, n);
    return 0;
}