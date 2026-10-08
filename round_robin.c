#include <stdio.h>

#define MAX_PROCESSES 100
#define MAX_TIME      10000

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining burst time
    int finish;     // Finish time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int inQueue;    // Flag: already added to ready queue?
};

// Simple circular queue for Round Robin
int queue[MAX_TIME];
int front = 0, rear = 0;
int i,j;
void enqueue(int pid)  { queue[rear++] = pid; }
int  dequeue()         { return queue[front++]; }
int  isEmpty()         { return front == rear; }

// Sort by arrival time
void sortByArrival(struct Process p[], int n) {
    for ( i = 0; i < n - 1; i++) {
        int min = i;
        for ( j = i + 1; j < n; j++)
            if (p[j].arrival < p[min].arrival)
                min = j;
        struct Process tmp = p[min]; p[min] = p[i]; p[i] = tmp;
    }
}

void roundRobin(struct Process p[], int n, int quantum) {
    sortByArrival(p, n);

    for ( i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
        p[i].inQueue   = 0;
    }

    int time = 0, completed = 0;

    // Enqueue the first arriving process(es)
    for ( i = 0; i < n; i++) {
        if (p[i].arrival <= time) {
            enqueue(i);
            p[i].inQueue = 1;
        }
    }

    while (completed < n) {
        if (isEmpty()) {
            // CPU idle — find next arriving process
            int nextArrival = MAX_TIME;
            for ( i = 0; i < n; i++)
                if (!p[i].inQueue && p[i].remaining > 0 && p[i].arrival < nextArrival)
                    nextArrival = p[i].arrival;
            time = nextArrival;
            for ( i = 0; i < n; i++) {
                if (!p[i].inQueue && p[i].remaining > 0 && p[i].arrival <= time) {
                    enqueue(i);
                    p[i].inQueue = 1;
                }
            }
            continue;
        }

        int idx = dequeue();

        // Run for min(quantum, remaining)
        int execTime = (p[idx].remaining < quantum) ? p[idx].remaining : quantum;
        p[idx].remaining -= execTime;
        time             += execTime;

        // Enqueue newly arrived processes during this time slice
        for ( i = 0; i < n; i++) {
            if (!p[i].inQueue && p[i].remaining > 0 && p[i].arrival <= time) {
                enqueue(i);
                p[i].inQueue = 1;
            }
        }

        if (p[idx].remaining == 0) {
            // Process finished
            completed++;
            p[idx].finish     = time;
            p[idx].turnaround = p[idx].finish - p[idx].arrival;
            p[idx].waiting    = p[idx].turnaround - p[idx].burst;
        } else {
            // Re-enqueue (current process goes back to the end of the queue)
            enqueue(idx);
        }
    }
}

void printResults(struct Process p[], int n, int quantum, const char *title) {
    // Sort by PID for clean display
    for ( i = 0; i < n - 1; i++)
        for ( j = i + 1; j < n; j++)
            if (p[j].pid < p[i].pid) {
                struct Process tmp = p[i]; p[i] = p[j]; p[j] = tmp;
            }

    printf("\n========== %s ==========\n", title);
    printf("Time Quantum: %d\n\n", quantum);
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
    int n, quantum;
    printf("=== Round Robin (RR) Scheduling ===\n");
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

    printf("\nEnter Time Quantum: ");
    scanf("%d", &quantum);

    roundRobin(p, n, quantum);
    printResults(p, n, quantum, "Round Robin (RR) Scheduling");

    return 0;
}
