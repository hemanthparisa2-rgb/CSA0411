#include <stdio.h>
#include <stdlib.h>

// Structure to represent a block
struct Block {
    int blockNumber;
    char data[256];
};

int main() {
    FILE *file;
    struct Block block;
    int blockNumber;

    // Index block (stores file offsets of blocks)
    long indexBlock[100];
    int i;

    // Initialize index block
    for (i = 0; i < 100; i++) {
        indexBlock[i] = -1;   // -1 means EMPTY
    }

    // Open or create the file in binary write mode
    file = fopen("indexed_file.txt", "wb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("Enter blocks (Enter '0' as block number to stop writing):\n");

    while (1) {
        printf("Block Number: ");
        scanf("%d", &block.blockNumber);

        if (block.blockNumber == 0)
            break;

        printf("Data: ");
        scanf(" %[^\n]", block.data);

        // Get current position (offset) BEFORE writing
        long position = ftell(file);

        fwrite(&block, sizeof(struct Block), 1, file);

        indexBlock[block.blockNumber] = position;
    }

    fclose(file);

    // Reopen file for reading
    file = fopen("indexed_file.txt", "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    while (1) {
        printf("\nEnter block number to read (0 to exit): ");
        scanf("%d", &blockNumber);

        if (blockNumber == 0)
            break;

        if (indexBlock[blockNumber] == -1) {
            printf("Block not found.\n");
        } else {
            // Move to block location
            fseek(file, indexBlock[blockNumber], SEEK_SET);

            fread(&block, sizeof(struct Block), 1, file);

            printf("\nBlock Found:\n");
            printf("Block Number: %d\n", block.blockNumber);
            printf("Data: %s\n", block.data);
        }
    }

    fclose(file);
    return 0;
}
