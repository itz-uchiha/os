#include <stdio.h>
#define MAX 100

void display(int frames[], int capacity)
{
    for (int i = 0; i < capacity; i++)
    {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int main()
{
    int pages[MAX], frames[MAX], recent[MAX];
    int n, capacity;
    int faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    for (int i = 0; i < capacity; i++)
    {
        frames[i] = -1;
        recent[i] = -1;
    }

    printf("\n--- LRU Page Replacement ---\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = -1;

        // Check if page is already present
        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] == page)
            {
                found = j;
                break;
            }
        }

        if (found != -1)
        {
            // Page hit: update last-used time
            recent[found] = i;
        }
        else
        {
            // Page fault
            int replace = -1;

            // Find empty frame
            for (int j = 0; j < capacity; j++)
            {
                if (frames[j] == -1)
                {
                    replace = j;
                    break;
                }
            }

            // No empty frame: find least recently used frame
            if (replace == -1)
            {
                replace = 0;
                for (int j = 1; j < capacity; j++)
                {
                    if (recent[j] < recent[replace])
                        replace = j;
                }
            }

            frames[replace] = page;
            recent[replace] = i;
            faults++;

            printf("Page %d -> ", page);
            display(frames, capacity);
        }
    }

    printf("\nTotal Page Faults = %d\n", faults);
    printf("Page Fault Ratio = %.2f\n", (float)faults / n);
    printf("Page Fault Percentage = %.2f%%\n", (float)faults * 100 / n);

    return 0;
}
