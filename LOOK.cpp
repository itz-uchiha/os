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
/* Sort the requests in ascending order. */ for (int i = 0; i < n - 1; i++) {
for (int j = i + 1; j < n; j++) { if (request[i] > request[j]) {
int temp = request[i]; request[i] = request[j]; request[j] = temp;
}
}
}
int split = 0;
 
while (split < n && request[split] < head) split++;
printf("Head path: %d", head);
/* First move towards higher cylinder numbers. */ for (int i = split; i < n; i++)
moveHead(request[i], &head, &total);
/* Reverse at the last request, not the disk end. */ for (int i = split - 1; i >= 0; i--)
moveHead(request[i], &head, &total);
printf("\nTotal head movement = %d cylinders\n", total); printf("Average head movement = %.2f cylinders\n",
(double)total / n); return 0;
}

