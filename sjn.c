#include <stdio.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int start;      // Start time
    int finish;     // Finish time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int done;       // Flag: 1 if completed
};
int i,j;
void sjn(struct Process p[], int n) {
    int completed = 0, time = 0;

    for ( i = 0; i < n; i++)
        p[i].done = 0;

    while (completed < n) {
        // Find arrived, not-done process with shortest burst time
        int idx = -1;
        int minBurst = INT_MAX;

        for ( i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= time) {
                if (p[i].burst < minBurst) {
                    minBurst = p[i].burst;
                    idx = i;
                } else if (p[i].burst == minBurst) {
                    // Tie-break: earlier arrival wins
                    if (p[i].arrival < p[idx].arrival)
                        idx = i;
                }
            }
        }

        if (idx == -1) {
            // No process available — advance time to next arrival
            int nextArrival = INT_MAX;
            for ( i = 0; i < n; i++)
                if (!p[i].done && p[i].arrival < nextArrival)
                    nextArrival = p[i].arrival;
            time = nextArrival;
            continue;
        }

        // Run the selected process to completion (non-preemptive)
        p[idx].start      = time;
        p[idx].finish     = time + p[idx].burst;
        p[idx].turnaround = p[idx].finish - p[idx].arrival;
        p[idx].waiting    = p[idx].turnaround - p[idx].burst;
        p[idx].done       = 1;
        time              = p[idx].finish;
        completed++;
    }
}

void printResults(struct Process p[], int n, const char *title) {
    // Sort by finish time for display
    for ( i = 0; i < n - 1; i++)
        for ( j = i + 1; j < n; j++)
            if (p[j].start < p[i].start) {
                struct Process tmp = p[i]; p[i] = p[j]; p[j] = tmp;
            }

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
    printf(" Shortest Job Next (SJN)\n ");
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

    sjn(p, n);
    printResults(p, n, "Shortest Job Next (SJN) — Non-Preemptive");

    return 0;
}
