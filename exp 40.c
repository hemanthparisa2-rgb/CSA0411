#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char filename[] = "file.txt";

    // Windows-compatible permissions (read + write)
    int new_permissions = _S_IREAD | _S_IWRITE;

    if (chmod(filename, new_permissions) == 0) {
        printf("File permissions changed successfully.\n");
    } else {
        perror("chmod");
        return 1;
    }

    return 0;
}
