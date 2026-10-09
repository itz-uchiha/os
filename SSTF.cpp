#include <stdio.h> 
#include <stdlib.h> 
#define MAX 100
#define DISK_SIZE 200
void moveHead(int next, int *head, int *total) {
*total += abs(next - *head);
*head = next;
printf(" -> %d", next);
}
int main(void) {
int request[MAX], n, head, total = 0; printf("Enter number of requests: ");
if (scanf("%d", &n) != 1 || n < 1 || n > MAX) return 1;
printf("Enter request queue: "); for (int i = 0; i < n; i++) {
if (scanf("%d", &request[i]) != 1 ||
request[i] < 0 || request[i] >= DISK_SIZE) return 1;
}
printf("Enter initial head position: "); if (scanf("%d", &head) != 1 ||
head < 0 || head >= DISK_SIZE) return 1;
int visited[MAX] = {0}; printf("Head path: %d", head);
for (int count = 0; count < n; count++) { int nearest = -1;
 
int minDistance = DISK_SIZE; for (int i = 0; i < n; i++) {
int distance = abs(request[i] - head);
if (!visited[i] && distance < minDistance) { minDistance = distance;
nearest = i;
}
}
visited[nearest] = 1; moveHead(request[nearest], &head, &total);
}
printf("\nTotal head movement = %d cylinders\n", total); printf("Average head movement = %.2f cylinders\n",
(double)total / n); return 0;
}
