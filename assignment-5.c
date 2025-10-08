#include <stdio.h>
void MFT() {
    int total_memory, block_size, num_process, memory_required[10];
    int blocks, allocated[10] = {0}, internal_frag[10] = {0};
    int total_internal_frag = 0, external_frag = 0, i, j = 0;

    printf("\n--- MFT (Multiprogramming with Fixed Tasks) ---\n");
    printf("Enter total memory available (in Bytes): ");
    scanf("%d", &total_memory);
    printf("Enter block size (in Bytes): ");
    scanf("%d", &block_size);
    printf("Enter number of processes: ");
    scanf("%d", &num_process);

    blocks = total_memory / block_size;
    printf("\nNumber of Blocks available in memory = %d\n", blocks);
    for (i = 0; i < num_process; i++) {
        printf("Enter memory required for process %d (in Bytes): ", i + 1);
        scanf("%d", &memory_required[i]);
    }
    printf("\nPROCESS\tMEMORY REQUIRED\tALLOCATED\tINTERNAL FRAGMENTATION\n");
    for (i = 0; i < num_process && j < blocks; i++) {
        if (memory_required[i] > block_size) {
            printf("%d\t\t%d\t\tNO\t\t---\n", i + 1, memory_required[i]);
            allocated[i] = 0;
        } else {
            allocated[i] = 1;
            internal_frag[i] = block_size - memory_required[i];
            total_internal_frag += internal_frag[i];
            printf("%d\t\t%d\t\tYES\t\t%d\n", i + 1, memory_required[i], internal_frag[i]);
            j++;
        }
    }
    if (i < num_process)
        printf("\nMemory is full; the remaining processes cannot be accommodated.\n");

    external_frag = total_memory - (blocks * block_size);
    printf("Total Internal Fragmentation = %d\n", total_internal_frag);
    printf("Total External Fragmentation = %d\n", external_frag);
}
void MVT() {
    int total_memory, allocated[10], memory_required, total_allocated = 0;
    int i = 0;
    char choice;

    printf("\n--- MVT (Multiprogramming with Variable Tasks) ---\n");
    printf("Enter total memory available (in Bytes): ");
    scanf("%d", &total_memory);

    do {
        printf("Enter memory required for process %d (in Bytes): ", i + 1);
        scanf("%d", &memory_required);

        if (memory_required <= (total_memory - total_allocated)) {
            allocated[i] = memory_required;
            total_allocated += memory_required;
            printf("Memory is allocated for Process %d\n", i + 1);
            i++;
        } else {
            printf("Memory is Full\n");
            break;
        }
        printf("Do you want to continue (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    printf("\nPROCESS\tMEMORY ALLOCATED\n");
    for (int k = 0; k < i; k++)
        printf("%d\t\t%d\n", k + 1, allocated[k]);

    printf("\nTotal Memory Allocated = %d\n", total_allocated);
    printf("Total External Fragmentation = %d\n", total_memory - total_allocated);
}
int main() {
    MFT();
    MVT();
}
