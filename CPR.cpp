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
    int pages[MAX], frames[MAX], reference[MAX];
    int n, capacity;
    int pointer = 0;
    int faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    // Initialize frames and reference bits
    for (int i = 0; i < capacity; i++)
    {
        frames[i] = -1;
        reference[i] = 0;
    }

    printf("\n--- Clock Page Replacement ---\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = -1;

        // Check whether page is present
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
            // Page hit: set reference bit
            reference[found] = 1;
        }
        else
        {
            // Page fault: find frame with reference bit 0
            while (reference[pointer] == 1)
            {
                reference[pointer] = 0;
                pointer = (pointer + 1) % capacity;
            }

            frames[pointer] = page;
            reference[pointer] = 1;
            pointer = (pointer + 1) % capacity;
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
