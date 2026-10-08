#include <stdio.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int priority;   // Priority (lower number = higher priority)
    int remaining;  // Remaining burst time
    int finish;     // Finish time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int started;    // Flag: has the process started?
};
int i,j;
void preemptivePriority(struct Process p[], int n) {
    int completed = 0, time = 0;
    int totalBurst = 0;

    for ( i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].started   = 0;
        totalBurst    += p[i].burst;
    }

    while (completed < n) {
        // Find process with highest priority (lowest number) among arrived processes
        int idx = -1;
        int bestPriority = INT_MAX;

        for ( i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].priority < bestPriority) {
                    bestPriority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == bestPriority) {
                    // Tie-break: earlier arrival wins
                    if (p[i].arrival < p[idx].arrival)
                        idx = i;
                }
            }
        }

        if (idx == -1) {
            // CPU is idle
            time++;
            continue;
        }

        p[idx].remaining--;
        time++;

        if (p[idx].remaining == 0) {
            completed++;
            p[idx].finish     = time;
            p[idx].turnaround = p[idx].finish - p[idx].arrival;
            p[idx].waiting    = p[idx].turnaround - p[idx].burst;
        }
    }
}

void printResults(struct Process p[], int n, const char *title) {
    printf("\n========== %s ==========\n", title);
    printf("%-6s %-10s %-8s %-10s %-8s %-10s %-10s\n",
           "PID", "Arrival", "Burst", "Priority", "Finish", "Waiting", "Turnaround");
    printf("-------------------------------------------------------------------\n");

    float totalWT = 0, totalTAT = 0;
    for ( i = 0; i < n; i++) {
        printf("%-6d %-10d %-8d %-10d %-8d %-10d %-10d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].priority, p[i].finish,
               p[i].waiting, p[i].turnaround);
        totalWT  += p[i].waiting;
        totalTAT += p[i].turnaround;
    }
    printf("-------------------------------------------------------------------\n");
    printf("Average Waiting Time    : %.2f\n", totalWT  / n);
    printf("Average Turnaround Time : %.2f\n", totalTAT / n);
}

int main() {
    int n;
    printf("=== Preemptive Priority Scheduling ===\n");
    printf("(Lower priority number = Higher priority)\n");
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
        printf("  Priority     : ");
        scanf("%d", &p[i].priority);
    }

    preemptivePriority(p, n);
    printResults(p, n, "Preemptive Priority Scheduling");

    return 0;
}
