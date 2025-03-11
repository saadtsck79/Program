#include<stdio.h>

struct Process { int id, at, bt, rt, ct, wt, tat; };

void find_srtf(struct Process p[], int n) {
    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;
    while(completed < n) {
        int min_index = -1;
        for(int i = 0; i < n; i++) 
            if(p[i].at <= time && p[i].rt > 0 && (min_index == -1 || p[i].rt < p[min_index].rt)) min_index = i;
        if(min_index != -1) {
            p[min_index].rt--;
            if(p[min_index].rt == 0) {
                p[min_index].ct = ++time;
                p[min_index].tat = p[min_index].ct - p[min_index].at;
                p[min_index].wt = p[min_index].tat - p[min_index].bt;
                total_wt += p[min_index].wt;
                total_tat += p[min_index].tat;
                completed++;
            }
        } else time++;
    }
    for(int i = 0; i < n; i++) 
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
    printf("\nAvg WT: %.2f  Avg TAT: %.2f", total_wt/n, total_tat/n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter AT and BT for process %d: ", i + 1);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }
    find_srtf(p, n);
    return 0;
}