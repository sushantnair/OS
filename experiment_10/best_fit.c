#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 4
#define MAX_JOBS 4

typedef struct {
    int memory_location;
    int size;
    char job_number[3];
    int job_size;
    char status[4];
    int internal_fragmentation;
} MemoryBlock;

typedef struct {
    char job_number[3];
    int job_size;
} Job;

void bestFit(MemoryBlock blocks[], Job jobs[]) {
    int total_available = 0;
    int total_used = 0;

    for (int i = 0; i < MAX_BLOCKS; i++) {
        total_available += blocks[i].size;
        blocks[i].status[0] = 'F';
    }

    for (int i = 0; i < MAX_JOBS; i++) {
        int best_fit_index = -1;
        int best_fit_size = -1;

        for (int j = 0; j < MAX_BLOCKS; j++) {
            if (blocks[j].status[0] == 'F' && blocks[j].size >= jobs[i].job_size) {
                if (best_fit_index == -1 || blocks[j].size < best_fit_size) {
                    best_fit_index = j;
                    best_fit_size = blocks[j].size;
                }
            }
        }

        if (best_fit_index != -1) {
            blocks[best_fit_index].status[0] = 'B';
            strcpy(blocks[best_fit_index].job_number, jobs[i].job_number);
            blocks[best_fit_index].job_size = jobs[i].job_size;
            blocks[best_fit_index].internal_fragmentation = blocks[best_fit_index].size - jobs[i].job_size;
            total_used += jobs[i].job_size;
        }
    }

    printf("Memory Location\tMemory Block Size\tJob Number\tJob Size\tStatus\tInternal Fragmentation\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("%d\t\t%d K\t\t\t%s\t\t%dK\t\t%s\t", blocks[i].memory_location, blocks[i].size, blocks[i].job_number, blocks[i].job_size, blocks[i].status);

        if (blocks[i].internal_fragmentation == 0) {
            printf("None\n");
        } else {
            printf("%d K\n", blocks[i].internal_fragmentation);
        }
    }

    printf("Total available: %dK  Total used: %dK  Internal Fragmentation: %dK\n", total_available, total_used, total_available - total_used);
}

int main() {
    MemoryBlock memory_blocks[MAX_BLOCKS] = {
        {10567, 30, "", 0, "", 0},
        {30457, 50, "", 0, "", 0},
        {300875, 200, "", 0, "", 0},
        {809567, 700, "", 0, "", 0}
    };

    Job jobs[MAX_JOBS] = {
        {"J1", 20},
        {"J2", 200},
        {"J3", 500},
        {"J4", 50}
    };

    bestFit(memory_blocks, jobs);

    return 0;
}
