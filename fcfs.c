#include <stdio.h>

struct Process {
    int pid;        
    int arrival;    
    int burst;     
    int start;      
    int finish;     
    int waiting;   
    int turnaround; 
};
int i,j;
void sortByArrival(struct Process p[], int n) {
    for (i = 0; i < n - 1; i++) {
        int min = i;
        for ( j = i + 1; j < n; j++)
            if (p[j].arrival < p[min].arrival)
                min = j;
        struct Process temp = p[min];
        p[min] = p[i];
        p[i] = temp;
    }
}

void fcfs(struct Process p[], int n) {
    sortByArrival(p, n);

    int time = 0;
    for ( i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival; 

        p[i].start      = time;
        p[i].finish     = time + p[i].burst;
        p[i].turnaround = p[i].finish - p[i].arrival;
        p[i].waiting    = p[i].turnaround - p[i].burst;
        time            = p[i].finish;
    }
}

void printResults(struct Process p[], int n, const char *title) {
    printf("\n========== %s ==========\n", title);
    printf("%-6s %-10s %-8s %-8s %-10s %-10s %-10s\n",
           "PID", "Arrival", "Burst", "Start", "Finish", "Waiting", "Turnaround");
    printf("---------------------------------------------------------------\n");

    float totalWT = 0, totalTAT = 0;
    for ( i = 0; i < n; i++) {
        printf("%-6d %-10d %-8d %-8d %-10d %-10d %-10d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].start, p[i].finish,
               p[i].waiting, p[i].turnaround);
        totalWT  += p[i].waiting;
        totalTAT += p[i].turnaround;
    }
    printf("---------------------------------------------------------------\n");
    printf("Average Waiting Time    : %.2f\n", totalWT  / n);
    printf("Average Turnaround Time : %.2f\n", totalTAT / n);
}

int main() {
    int n;
    printf("=== First Come First Serve (FCFS) Scheduling ===\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for ( i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess P%d:\n", p[i].pid);
        printf("  Arrival Time : ");
        scanf("%d", &p[i].arrival);
        printf("  Burst Time   : ");
        scanf("%d", &p[i].burst);
    }

    fcfs(p, n);
    printResults(p, n, "First Come First Serve (FCFS)");

    return 0;
}
