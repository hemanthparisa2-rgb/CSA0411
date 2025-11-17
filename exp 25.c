#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <io.h>     // Windows _open()
#include <sys/stat.h>

int main() {

    // Windows version uses _open instead of open
    int fd = _open("foo.txt", _O_RDONLY | _O_CREAT, _S_IREAD | _S_IWRITE);

    printf("fd = %d\n", fd);

    if (fd == -1) {
        printf("Error Number: %d\n", errno);
        perror("Program");
    } else {
        printf("File opened/created successfully.\n");
    }

    _close(fd);

    system("pause");   // <-- keeps output window open
    return 0;
}
