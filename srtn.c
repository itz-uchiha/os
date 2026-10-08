#include <stdio.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining burst time
    int finish;     // Finish time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
};
int i,j;
void srtn(struct Process p[], int n) {
    int completed = 0, time = 0;

    for ( i = 0; i < n; i++)
        p[i].remaining = p[i].burst;

    while (completed < n) {
        // Find arrived process with shortest remaining time
        int idx = -1;
        int minRemaining = INT_MAX;

        for ( i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].remaining < minRemaining) {
                    minRemaining = p[i].remaining;
                    idx = i;
                } else if (p[i].remaining == minRemaining) {
                    // Tie-break: earlier arrival wins
                    if (p[i].arrival < p[idx].arrival)
                        idx = i;
                }
            }
        }

        if (idx == -1) {
            // CPU idle â€” jump to next arrival
            int nextArrival = INT_MAX;
            for ( i = 0; i < n; i++)
                if (p[i].remaining > 0 && p[i].arrival < nextArrival)
                    nextArrival = p[i].arrival;
            time = nextArrival;
            continue;
        }

        // Execute selected process for 1 unit of time
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
    printf("%-6s %-10s %-8s %-8s %-10s %-10s\n",
           "PID", "Arrival", "Burst", "Finish", "Waiting", "Turnaround");
    printf("------------------------------------------------------\n");

    float totalWT = 0, totalTAT = 0;
    for ( i = 0; i < n; i++) {
        printf("%-6d %-10d %-8d %-8d %-10d %-10d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].finish, p[i].waiting, p[i].turnaround);
        totalWT  += p[i].waiting;
        totalTAT += p[i].turnaround;
    }
    printf("------------------------------------------------------\n");
    printf("Average Waiting Time    : %.2f\n", totalWT  / n);
    printf("Average Turnaround Time : %.2f\n", totalTAT / n);
}

int main() {
    int n;
    printf("=== Shortest Remaining Time Next (SRTN) ===\n");
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

    srtn(p, n);
    printResults(p, n, "Shortest Remaining Time Next (SRTN) ” Preemptive");

    return 0;
}
