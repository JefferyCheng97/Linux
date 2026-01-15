#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int fd = open("write_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    clock_t start = clock();

    for (int i = 0; i < 1000000; i++) {
        if (write(fd, "a", 1) != 1) {
            perror("write");
            close(fd);
            exit(1);
        }
    }

    close(fd);

    clock_t end = clock();
    printf("write: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
