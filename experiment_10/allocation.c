#include <stdio.h>
#include <stdbool.h>

// Define jobs
struct Job {
    char name;
    int size;
};

// Structure to represent memory blocks
struct MemoryBlock {
    int location;
    int size;
    bool isBusy;
    char jobName;
    int jobSize;
};

// Function to perform First Fit memory allocation
void first_fit(struct MemoryBlock memoryBlocks[], int numBlocks, struct Job jobs[], int numJobs) {
    int totalAvailable = 0;
    int totalUsed = 0;
    int internalFragmentation = 0;

    printf("Memory Location\tMemory Block Size\tJob Number\tJob Size\tStatus\tInternal Fragmentation\n");

    for (int i = 0; i < numJobs; i++) {
        for (int j = 0; j < numBlocks; j++) {
            if (!memoryBlocks[j].isBusy && memoryBlocks[j].size >= jobs[i].size) {
                totalAvailable += memoryBlocks[j].size;
                memoryBlocks[j].isBusy = true;
                memoryBlocks[j].jobName = jobs[i].name;
                memoryBlocks[j].jobSize = jobs[i].size;

                totalUsed += jobs[i].size;
                internalFragmentation += memoryBlocks[j].size - jobs[i].size;

                printf("%d\t\t%d K\t\t\tJ%c\t\t%d K\t\tBusy\t%d K\n", memoryBlocks[j].location, memoryBlocks[j].size, memoryBlocks[j].jobName, jobs[i].size, memoryBlocks[j].size - jobs[i].size);
                break;
            }
        }
    }

    for (int i = 0; i < numBlocks; i++) {
        if (!memoryBlocks[i].isBusy) {
            totalAvailable += memoryBlocks[i].size;
            printf("%d\t\t%d K\t\t\t\t\t\t\tFree\t%d K\n", memoryBlocks[i].location, memoryBlocks[i].size, memoryBlocks[i].size);
            internalFragmentation += memoryBlocks[i].size; // Add unused memory block to internal fragmentation
        }
    }

    printf("Total available:\t%d K\tTotal used:\t%d K\tInternal Fragmentation:\t%d K\n", totalAvailable, totalUsed, internalFragmentation);
}

// Function to perform Best Fit memory allocation
void bestFit(struct MemoryBlock blocks[], int numBlocks, struct Job jobs[], int numJobs) {
    int totalAvailable = 0;
    int totalUsed = 0;

    for (int i = 0; i < numBlocks; i++) {
        totalAvailable += blocks[i].size;
        blocks[i].isBusy = false;
    }

    for (int i = 0; i < numJobs; i++) {
        int best_fit_index = -1;
        int best_fit_size = -1;

        for (int j = 0; j < numBlocks; j++) {
            if (!blocks[j].isBusy && blocks[j].size >= jobs[i].size) {
                if (best_fit_index == -1 || blocks[j].size < best_fit_size) {
                    best_fit_index = j;
                    best_fit_size = blocks[j].size;
                }
            }
        }

        if (best_fit_index != -1) {
            blocks[best_fit_index].isBusy = true;
            blocks[best_fit_index].jobName = jobs[i].name;
            blocks[best_fit_index].jobSize = jobs[i].size;

            totalUsed += jobs[i].size;
        }
    }

    int internalFragmentation = 0;

    printf("Memory Location\tMemory Block Size\tJob Number\tJob Size\tStatus\tInternal Fragmentation\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("%d\t\t%d K\t\t\tJ%c\t\t%d K\t\t%s\t", blocks[i].location, blocks[i].size, blocks[i].jobName, blocks[i].jobSize, (blocks[i].isBusy ? "Busy" : "Free"));

        if (blocks[i].isBusy) {
            internalFragmentation += blocks[i].size - blocks[i].jobSize;
            printf("%d K\n", blocks[i].size - blocks[i].jobSize);
        } else {
            printf("None\n");
        }
    }

    printf("Total available:\t%d K\tTotal used:\t%d K\tInternal Fragmentation:\t%d K\n", totalAvailable, totalUsed, internalFragmentation);
}

int main() {
    struct MemoryBlock memoryBlocks[] = {
        {300875, 200, false, 0, 0},
        {10567, 30, false, 0, 0},
        {809567, 700, false, 0, 0},
        {30457, 50, false, 0, 0}
    };

    struct Job jobs[] = {
        {'1', 20},
        {'2', 200},
        {'3', 500},
        {'4', 50}
    };

    int choice;
    do {
        printf("Memory Allocation Menu:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                first_fit(memoryBlocks, 4, jobs, 4);
                break;
            case 2:
                bestFit(memoryBlocks, 4, jobs, 4);
                break;
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
