#include <stdio.h>
#define MAX 100

int isPresent(int frames[], int capacity, int page)
{
    for (int i = 0; i < capacity; i++)
    {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

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

int findOptimal(int pages[], int n, int frames[], int capacity, int current)
{
    int farthest = -1;
    int index = -1;

    for (int i = 0; i < capacity; i++)
    {
        int j;

        // Find next use of current frame
        for (j = current + 1; j < n; j++)
        {
            if (frames[i] == pages[j])
                break;
        }

        // Page is never used again
        if (j == n)
            return i;

        // Find page used farthest in future
        if (j > farthest)
        {
            farthest = j;
            index = i;
        }
    }
    return index;
}

int main()
{
    int pages[MAX], frames[MAX];
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
        frames[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n");

    for (int i = 0; i < n; i++)
    {
        if (!isPresent(frames, capacity, pages[i]))
        {
            int empty = -1;

            // Find empty frame
            for (int j = 0; j < capacity; j++)
            {
                if (frames[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            if (empty != -1)
            {
                frames[empty] = pages[i];
            }
            else
            {
                int replace = findOptimal(pages, n, frames, capacity, i);
                frames[replace] = pages[i];
            }

            faults++;
            printf("Page %d -> ", pages[i]);
            display(frames, capacity);
        }
    }

    printf("\nTotal Page Faults = %d\n", faults);
    printf("Page Fault Ratio = %.2f\n", (float)faults / n);
    printf("Page Fault Percentage = %.2f%%\n", (float)faults * 100 / n);

    return 0;
}
