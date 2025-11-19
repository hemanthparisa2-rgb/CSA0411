#include <stdio.h>
#include <stdlib.h>

struct Block {
    int blockNumber;
    char data[256];
};

int main() {
    FILE *file;
    struct Block block;
    int blockNumber;

    // Index block stores the file positions of actual blocks
    long indexBlock[100];
    int i;

    for (i = 0; i < 100; i++) {
        indexBlock[i] = -1;  // -1 means "empty"
    }

    // Open file for writing blocks
    file = fopen("indexed_file.txt", "wb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Enter blocks (Enter 0 as block number to stop writing):\n");

    while (1) {
        printf("Block Number: ");
        scanf("%d", &block.blockNumber);

        if (block.blockNumber == 0)
            break;

        printf("Data: ");
        scanf(" %[^\n]", block.data);

        long pos = ftell(file);  // Position before writing block
        fwrite(&block, sizeof(struct Block), 1, file);

        indexBlock[block.blockNumber] = pos;  // store pointer
    }

    fclose(file);

    // Open file for reading
    file = fopen("indexed_file.txt", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (1) {
        printf("\nEnter block number to read (0 to exit): ");
        scanf("%d", &blockNumber);

        if (blockNumber == 0)
            break;

        if (indexBlock[blockNumber] == -1) {
            printf("Block not found!\n");
        } 
        else {
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
