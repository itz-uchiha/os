#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n; 
int m; 

int Allocation[MAX_PROCESSES][MAX_RESOURCES];
int Max[MAX_PROCESSES][MAX_RESOURCES];
int Need[MAX_PROCESSES][MAX_RESOURCES];
int Available[MAX_RESOURCES];

int i,j;
void calculateNeed() {
    for ( i = 0; i < n; i++)
        for ( j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
}


void printState() {
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for ( i = 0; i < n; i++) {
        printf("P%d\t", i);
        for ( j = 0; j < m; j++) printf("%d ", Allocation[i][j]);
        printf("\t\t");
        for ( j = 0; j < m; j++) printf("%d ", Max[i][j]);
        printf("\t\t");
        for ( j = 0; j < m; j++) printf("%d ", Need[i][j]);
        printf("\n");
    }
    printf("\nAvailable: ");
    for ( j = 0; j < m; j++) printf("%d ", Available[j]);
    printf("\n");
}

bool isSafe(int safeSeq[]) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};

    for ( j = 0; j < m; j++)
        work[j] = Available[j];

    int count = 0;
    while (count < n) {
        bool found = false;

        for ( i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for ( j = 0; j < m; j++) {
                    if (Need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                 
                    for ( j = 0; j < m; j++)
                        work[j] += Allocation[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
           
            return false;
        }
    }

    return true; 
}


bool requestResources(int pid, int request[]) {
  
    for ( j = 0; j < m; j++) {
        if (request[j] > Need[pid][j]) {
            printf("Error: Process P%d has exceeded its maximum claim.\n", pid);
            return false;
        }
    }


    for ( j = 0; j < m; j++) {
        if (request[j] > Available[j]) {
            printf("Process P%d must wait; resources are not available.\n", pid);
            return false;
        }
    }


    for ( j = 0; j < m; j++) {
        Available[j]    -= request[j];
        Allocation[pid][j] += request[j];
        Need[pid][j]    -= request[j];
    }


    int safeSeq[MAX_PROCESSES];
    if (isSafe(safeSeq)) {
        printf("Request can be granted safely.\n");
        return true;
    } else {
     
        for ( j = 0; j < m; j++) {
            Available[j]    += request[j];
            Allocation[pid][j] -= request[j];
            Need[pid][j]    += request[j];
        }
        printf("Request denied: granting it would leave the system unsafe.\n");
        return false;
    }
}

int main() {
    printf("=== Banker's Algorithm - Deadlock Avoidance ===\n\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Available resources vector (%d values):\n", m);
    for ( j = 0; j < m; j++)
        scanf("%d", &Available[j]);

    printf("\nEnter Max matrix (%d x %d):\n", n, m);
    for ( i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for ( j = 0; j < m; j++)
            scanf("%d", &Max[i][j]);
    }

    printf("\nEnter Allocation matrix (%d x %d):\n", n, m);
    for ( i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for ( j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);
    }

    calculateNeed();
    printState();

 
    int safeSeq[MAX_PROCESSES];
    if (isSafe(safeSeq)) {
        printf("\nSystem is in a SAFE state.\nSafe sequence: ");
        for ( i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("\nSystem is NOT in a safe state (deadlock risk).\n");
    }


    char choice;
    printf("\nDo you want to test a resource request? (y/n): ");
    scanf(" %c", &choice);

    while (choice == 'y' || choice == 'Y') {
        int pid;
        int request[MAX_RESOURCES];

        printf("Enter process number requesting resources (0 - %d): ", n - 1);
        scanf("%d", &pid);

        printf("Enter request vector (%d values): ", m);
        for ( j = 0; j < m; j++)
            scanf("%d", &request[j]);

        requestResources(pid, request);
        printState();

        printf("\nTest another request? (y/n): ");
        scanf(" %c", &choice);
    }

    return 0;
}
