#include <stdio.h>
#define MAX 100
int isPresent(int frames[], int capacity, int page) { 
for (int i = 0; i < capacity; i++) {
if (frames[i] == page) return 1;
}
return 0;
}
void display(int frames[], int capacity) { for (int i = 0; i < capacity; i++) {
if (frames[i] == -1) printf("- ");
else
printf("%d ", frames[i]);
}
printf("\n");
}
 
int main() {
int pages[MAX], frames[MAX]; int n, capacity;
int pointer = 0, faults = 0; printf("Enter number of pages: "); scanf("%d", &n);
printf("Enter reference string:\n"); for (int i = 0; i < n; i++)
scanf("%d", &pages[i]); printf("Enter number of frames: "); scanf("%d", &capacity);
for (int i = 0; i < capacity; i++) frames[i] = -1;
printf("\n--- FIFO Page Replacement ---\n"); for (int i = 0; i < n; i++) {

if (!isPresent(frames, capacity, pages[i])) { frames[pointer] = pages[i];
pointer = (pointer + 1) % capacity; faults++;
printf("Page %d -> ", pages[i]); display(frames, capacity);
}
}
printf("\nTotal Page Faults = %d\n", faults); printf("Page Fault Ratio = %.2f\n", (float)faults / n); printf("Page Fault Percentage = %.2f%%\n",
(float)faults * 100 / n); return 0;
}

